#!/usr/bin/env python3
#
# Copyright (c) 2020-2021 The Eleccoin Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.
#
# Download or build previous releases.
# Needs curl and tar to download a release, or the build dependencies when
# building a release.

import argparse
import contextlib
from fnmatch import fnmatch
import os
from pathlib import Path
import re
import shutil
import subprocess
import sys
import hashlib


SHA256_SUMS = {
"c84cbbf7b919864f9d01672a69d470b548166d418c41de2df8d408acfe2f3e97":  "eleccoin-1.2.1-aarch64-linux-gnu-debug.tar.gz"
"1bc18ed354cb0b492c69868e34f68eb2c8842f789970a627f8dca798434392e8":  "eleccoin-1.2.1-aarch64-linux-gnu.tar.gz"
"d20c5641c20b91fac8b047da48a94f9a599cb557b1998c8ce3500c3cbc3eebcd":  "eleccoin-1.2.1-arm-linux-gnueabihf-debug.tar.gz"
"f3730c44227fbc2c0450d1ed61a5ea1e6f373c219372431f9d9f7ade50814377":  "eleccoin-1.2.1-arm-linux-gnueabihf.tar.gz"
"61372b4e100f6ec51fcd08f04ec261ee9e9ea6ea2c851f0245816c4cf035505a":  "eleccoin-1.2.1-osx64.tar.gz"
"71b375c4f9e65d1ffdfc1b5241c04336d825aab82f1ceb1e40408d04701a6bfc":  "eleccoin-1.2.1-osx.dmg"
"6d7c8def10c65a14121796fc52b257b38948cb6d26db926e9e807bffdd4bc49a":  "eleccoin-1.2.1-osx-unsigned.dmg"
"72a75e8b52b3074536c21d03ccb238335ee200b820a469dcfc76ac0e32075503":  "eleccoin-1.2.1-osx-unsigned.tar.gz"
"08ba90bd7b62de240193758460e472490af7ec2acd97d1ac5248caac232a2a37":  "eleccoin-1.2.1.tar.gz"
"da334e16eecdbaaf1841a052d8442b6b210aedb27de276d2bb484c9dc59c6fae":  "eleccoin-1.2.1-win64-debug.zip"
"5d6279c8f625b5d4bc0829ecb08c71f7debf20d3f5b6969715afa8bc7d374dba":  "eleccoin-1.2.1-win64-setup.exe"
"02c25de771863b42a967da97ed8607822116c2b2440999188ddded6784cbcabe":  "eleccoin-1.2.1-win64-setup-unsigned.exe"
"62d6532a864b4ff62957827681578012c5c9b714e46c0eb0969a78022636df29":  "eleccoin-1.2.1-win64.zip"
"8bb166a6c9dfae51d208a73e81b34d8b707463029b08273f188f4e689c2c3c0a":  "eleccoin-1.2.1-win-unsigned.tar.gz"
"7c45360bea2c052a26bb52ca70f6064dc39b6b4be86b09262bc22422ad22a643":  "eleccoin-1.2.1-x86_64-linux-gnu-debug.tar.gz"
"f96c39ae406374d4d5745ca2a2a1a9e2426a69e808ddd99c90953ec3a8d36355":  "eleccoin-1.2.1-x86_64-linux-gnu.tar.gz"
}

@contextlib.contextmanager
def pushd(new_dir) -> None:
    previous_dir = os.getcwd()
    os.chdir(new_dir)
    try:
        yield
    finally:
        os.chdir(previous_dir)


def download_binary(tag, args) -> int:
    if Path(tag).is_dir():
        if not args.remove_dir:
            print('Using cached {}'.format(tag))
            return 0
        shutil.rmtree(tag)
    Path(tag).mkdir()
    bin_path = 'bin/eleccoin-core-{}'.format(tag[1:])
    match = re.compile('v(.*)(rc[0-9]+)$').search(tag)
    if match:
        bin_path = 'bin/eleccoin-core-{}/test.{}'.format(
            match.group(1), match.group(2))
    tarball = 'eleccoin-{tag}-{platform}.tar.gz'.format(
        tag=tag[1:], platform=args.platform)
    tarballUrl = 'https://eleccoin.org/{bin_path}/{tarball}'.format(
        bin_path=bin_path, tarball=tarball)

    print('Fetching: {tarballUrl}'.format(tarballUrl=tarballUrl))

    header, status = subprocess.Popen(
        ['curl', '--head', tarballUrl], stdout=subprocess.PIPE).communicate()
    if re.search("404 Not Found", header.decode("utf-8")):
        print("Binary tag was not found")
        return 1

    curlCmds = [
        ['curl', '--remote-name', tarballUrl]
    ]

    for cmd in curlCmds:
        ret = subprocess.run(cmd).returncode
        if ret:
            return ret

    hasher = hashlib.sha256()
    with open(tarball, "rb") as afile:
        hasher.update(afile.read())
    tarballHash = hasher.hexdigest()

    if tarballHash not in SHA256_SUMS or SHA256_SUMS[tarballHash] != tarball:
        print("Checksum did not match")
        return 1
    print("Checksum matched")

    # Extract tarball
    ret = subprocess.run(['tar', '-zxf', tarball, '-C', tag,
                          '--strip-components=1',
                          'eleccoin-{tag}'.format(tag=tag[1:])]).returncode
    if ret:
        return ret

    Path(tarball).unlink()
    return 0


def build_release(tag, args) -> int:
    githubUrl = "https://github.com/eleccoin/eleccoin"
    if args.remove_dir:
        if Path(tag).is_dir():
            shutil.rmtree(tag)
    if not Path(tag).is_dir():
        # fetch new tags
        subprocess.run(
            ["git", "fetch", githubUrl, "--tags"])
        output = subprocess.check_output(['git', 'tag', '-l', tag])
        if not output:
            print('Tag {} not found'.format(tag))
            return 1
    ret = subprocess.run([
        'git', 'clone', githubUrl, tag
    ]).returncode
    if ret:
        return ret
    with pushd(tag):
        ret = subprocess.run(['git', 'checkout', tag]).returncode
        if ret:
            return ret
        host = args.host
        if args.depends:
            with pushd('depends'):
                ret = subprocess.run(['make', 'NO_QT=1']).returncode
                if ret:
                    return ret
                host = os.environ.get(
                    'HOST', subprocess.check_output(['./config.guess']))
        config_flags = '--prefix={pwd}/depends/{host} '.format(
            pwd=os.getcwd(),
            host=host) + args.config_flags
        cmds = [
            './autogen.sh',
            './configure {}'.format(config_flags),
            'make',
        ]
        for cmd in cmds:
            ret = subprocess.run(cmd.split()).returncode
            if ret:
                return ret
        # Move binaries, so they're in the same place as in the
        # release download
        Path('bin').mkdir(exist_ok=True)
        files = ['eleccoind', 'eleccoin-cli', 'eleccoin-tx']
        for f in files:
            Path('src/'+f).rename('bin/'+f)
    return 0


def check_host(args) -> int:
    args.host = os.environ.get('HOST', subprocess.check_output(
        './depends/config.guess').decode())
    if args.download_binary:
        platforms = {
            'aarch64-*-linux*': 'aarch64-linux-gnu',
            'x86_64-*-linux*': 'x86_64-linux-gnu',
            'x86_64-apple-darwin*': 'osx64',
        }
        args.platform = ''
        for pattern, target in platforms.items():
            if fnmatch(args.host, pattern):
                args.platform = target
        if not args.platform:
            print('Not sure which binary to download for {}'.format(args.host))
            return 1
    return 0


def main(args) -> int:
    Path(args.target_dir).mkdir(exist_ok=True, parents=True)
    print("Releases directory: {}".format(args.target_dir))
    ret = check_host(args)
    if ret:
        return ret
    if args.download_binary:
        with pushd(args.target_dir):
            for tag in args.tags:
                ret = download_binary(tag, args)
                if ret:
                    return ret
        return 0
    args.config_flags = os.environ.get('CONFIG_FLAGS', '')
    args.config_flags += ' --without-gui --disable-tests --disable-bench'
    with pushd(args.target_dir):
        for tag in args.tags:
            ret = build_release(tag, args)
            if ret:
                return ret
    return 0


if __name__ == '__main__':
    parser = argparse.ArgumentParser(
        formatter_class=argparse.ArgumentDefaultsHelpFormatter)
    parser.add_argument('-r', '--remove-dir', action='store_true',
                        help='remove existing directory.')
    parser.add_argument('-d', '--depends', action='store_true',
                        help='use depends.')
    parser.add_argument('-b', '--download-binary', action='store_true',
                        help='download release binary.')
    parser.add_argument('-t', '--target-dir', action='store',
                        help='target directory.', default='releases')
    parser.add_argument('tags', nargs='+',
                        help="release tags. e.g.: v0.18.1 v0.20.0rc2")
    args = parser.parse_args()
    sys.exit(main(args))
