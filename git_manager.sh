#!/bin/bash
#set -x
declare -A folder
_detailed_changes=$1
_switch=$2
_release=$3
_commit_string="Commit of `date +%Y%m%d` - `date +%s` - "               
_remote_alias="origin"                                                  
_main_branch="main"                                                     
_path=`pwd`                                                             
_MAXIMUMUM_PARAMS=1      
_FOLLOW_TAGS=false                                               
if [[ $# -lt $_MAXIMUMUM_PARAMS ]]
then
    echo "Wrong Syntax."
    echo "$_file_name commit_message [-switch, -switch2, ...]"
    echo -e "\t commit_message"
    echo -e "\t    Commit Message for git commit -m \"commit_message\""
    echo -e "\t switches"
    echo -e "\t    -t \t Follow incremental tagging"
    echo -e "\t    -m \t Minor Release"
    echo -e "\t    -M \t Major Release"
    echo -e "\t    -M \t Patch Release"
    echo ""
    echo -e "Sample: $_file_name \"commit message #1\" -t -p"
    exit
fi
if [[ $_switch != "" ]]
then
    if [[ $_switch == "-t" ]]
    then
        _FOLLOW_TAGS=true
        _OLD_TAG=`git tag | tail -n1`
        _minor=`echo $_OLD_TAG | awk -F. '{print $2}'`
        _major=`echo $_OLD_TAG | awk -F. '{print $1}' | awk -F"v" '{print $2}'  `
        _patch=`echo $_OLD_TAG | awk -F. '{print $3}' | awk -F- '{print $1}'`
        if [[ $_release == "-M" ]]
        then
            _minor=0
            _major=$(( _major + 1 ))
            _patch=0
        elif [[ $_release == "-m" ]]
        then
            _minor=$(( _minor + 1 ))
            _patch=0
            
        elif [[ $_release == "-p" ]]
        then
            _patch=$(( _patch + 1 )) 
        else    
            echo "Release switch $_release not coded"
            echo "Exiting"
            exit
        fi
        _NEW_TAG_WITHOUT_BUILD=`echo "v$_major.$_minor.$_patch"`
    else 
        echo "Switch $_switch not coded"
        echo "Exiting"
        exit
    fi  
else    
    _FOLLOW_TAGS=false
fi
if [[ $_detailed_changes == "init" ]]
then    
    if [[ $_github_user == "" ]]
    then
        read -p "Enter your gitHub User Name: " _github_user
    fi
    
    if [[ $_project_name == "" ]]
    then
        read -p "Enter your git repo name: " _project_name
    fi

    if [[ $_user_name == "" ]]
    then
        read -p "Enter your git username for commits: " _user_name
    fi

    if [[ $_email == "" ]]
    then
        read -p "Enter your git email for commits: " _email
    fi
    _file_name=$0
    _remote_project_name="https://github.com/$_github_user/$_project_name.git"  
    _comment_char="\\"                            

    rm -rf .git
    git init
    git config user.name "$_user_name"
    git config user.email $_email
    git config core.commentChar $_comment_char
    git remote remove $_remote_alias
    git remote add $_remote_alias $_remote_project_name
    git checkout -b $_main_branch
    git add *
    git commit -m "$_commit_string REPO INIT"
    _current_head=`git log --oneline | head -n1 | awk '{ print $1 }'`
    git tag v0.0.1 $_current_head
    git push -u $_remote_alias $_main_branch --force --follow-tagging   # overwrite REMOTE !!!!
else
    cd "${_path}"
    # array that contains folder names to run the commit onto
    folder[0,0]="/."
     # create other array entries if needed
    _len_array=${#folder[@]}
    for i in $((_len_array-1))  
    do
        cd  "$_path${folder[$i,0]}"
        git add -A
        _commit_counter=`git log --oneline | wc -l`
        _current_branch=`git branch | grep "*" | awk {'print $2'}`
        _old_head=`git log --oneline | head -n1 | awk '{ print $1 }'`
        git commit -m "#$((_commit_counter+1)) - $_commit_string$_detailed_changes"
        _current_head=`git log --oneline | head -n1 | awk '{ print $1 }'`
        if [[ $_old_head != $_current_head ]]
        then
            if [[ $_FOLLOW_TAGS == true ]]
            then 
                _build_number=$_current_head
                git tag $_NEW_TAG_WITHOUT_BUILD $_current_head
            fi
            if [[ $_current_branch != $_main_branch ]]
            then    
                git checkout $_main_branch
                git merge $_current_branch
            fi
            git push origin --tags -f
            git push origin
        fi
     
    done
fi
sh automatic_readme_generator.sh