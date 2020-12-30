#!/bin/bash
set -x
last_tag=`git tag | tail -n1`
_minor=`echo $last_tag | awk -F. '{print $2}'`
_major=`echo $last_tag | awk -F. '{print $1}' | awk -F"v" '{print $2}'  `


_NEW_TAG_WITHOUT_PATCH=`echo "v$_major.$_minor"`
_NEW_TAG_WITHOUT_MINOR=`echo "v$_major"`

echo "Cleaning all Patches release of non current tags"
for _ind in {0..$_minor}
do
    _minor=$(( _minor - _ind ))
    _NEW_TAG_WITHOUT_PATCH=`echo "v$_major.$_minor"`
done
#git tag -l "$_NEW_TAG_WITHOUT_PATCH*" | while read myTag;do git tag -d $myTag;done
#git push origin --tags
