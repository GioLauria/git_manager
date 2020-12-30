#set -x
declare -A tags
_first_commit=`git log --oneline | tail -n1 | awk '{print $1}'|sort -r`
_list_of_tags=`git tag`
_index_tags=0
_notes=""
for my_tag in `echo $_list_of_tags`
do
    tags[$_index_tags]="$my_tag"   
    _index_tags=$(( _index_tags + 1 )) 
done
_len_array=${#tags[@]} 

for (( _index_tags = 0; _index_tags< $_len_array ; _index_tags++))
do
    if [[ $_index_tags == 0 ]]
    then
        # the first output has to be the REPO INIT and his tag
        _notes=`echo -e "\n${tags[$_index_tags]}"`
        _notes=`echo -e "$_notes \n\`git log $_first_commit --oneline | grep \"Commit of\"\`"`      
    else
        _notes=`echo -e "$_notes \n${tags[$_index_tags]}"`
        _notes=`echo -e "$_notes \n\`git log ${tags[$((_index_tags-1))]}..${tags[$((_index_tags))]} --oneline | grep "Commit of"\`"`
        
    fi
    # Show orphan commits (With no tag parent)
    # if [[ $_index_tags == $((_len_array-1)) ]]
    # then
    #      _notes=`echo -e "$_notes \n\`git log ${tags[$((_index_tags))]}..HEAD --oneline | grep "Commit of"\`"`
    # fi     
done
sed -i '/RELEASE NOTES/q' README.md
sed -i '/RELEASE NOTES/r/dev/stdin' README.md <<<"$_notes"