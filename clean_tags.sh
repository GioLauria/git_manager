#!/bin/bash
#set -x
last_tag=`git tag | tail -n1` 
_minor=`echo $last_tag | awk -F. '{print $2}'`
_major=`echo $last_tag | awk -F. '{print $1}' | awk -F"v" '{print $2}'`

_NEW_TAG_WITHOUT_PATCH=`echo "v$_major.$_minor"`
_NEW_TAG_WITHOUT_MINOR=`echo "v$_major"`
_tags_to_remove=`git tag | grep -v "\.0" | grep -v "CURRENT" | grep -v "$_NEW_TAG_WITHOUT_PATCH"`

echo "Cleaning all Patches release of non current tags"
echo $_tags_to_remove
for my_tag in `echo $_tags_to_remove`
do
    git tag -d $my_tag
done
git push origin --tags --force
