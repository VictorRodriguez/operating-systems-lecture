import os
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('--dos2unix', dest='dos2unix', action='store_true')
parser.add_argument('--clean', dest='clean', action='store_true')
parser.add_argument('--check_apply', dest='check_apply', action='store_true')
args = parser.parse_args()

if args.dos2unix:
    print("Converting to Unix ..")
    cmd = "dos2unix patches/* > /dev/null 2>&1 "
    os.system(cmd)

if args.clean:
    print("Clean patches titles")

    for filename in os.listdir('patches/'):
        new_name = ''.join(e for e in filename if e.isalnum())
        new_name = os.path.join("patches/", new_name)
        os.rename(os.path.join("patches/",filename),new_name)

if args.check_apply:
    print("Check patch ... ")
    for patch in os.listdir('patches/'):
        patch = os.path.join("patches/",patch)
        patch_path =  os.path.abspath(patch)
        cmd = "git apply --check %s" % (patch_path)
        ret = os.system(cmd)
        if ret:
            print("PATCH does not apply")
            print patch
        else:
            print
            print("patch applying good")

