#set -x
declare -A tags
_first_commit=`git log --oneline | tail -n1 | awk '{print $1}'|sort -r`
_list_of_tags=`git tag`
_index_tags=0
_notes=""
_url=`git remote  -v | grep push | awk '{ print $2 }' | sed  s/'\.git'//g`

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
        #_notes=`echo -e "$_notes <br>-----------------------------<br>"`
        _notes=`echo -e "<b><a href="$_url/tree/${tags[$_index_tags]}">$_notes${tags[$_index_tags]}</a></b>"`
        _notes=`echo -e "$_notes <br>-----------------------------"`
        _temp_output_raw=`git log $_first_commit --oneline | grep "Commit of"`
        _notes=`echo -e "$_notes <br>$_temp_output_raw"`      
    else
        _notes=`echo -e "$_notes <br>-----------------------------<br>"`
        _notes=`echo -e "$_notes <b><a href="$_url/tree/${tags[$_index_tags]}">${tags[$_index_tags]}</a></b>"`
        _notes=`echo -e "$_notes <br>-----------------------------"`
        _temp_output_raw=`git log ${tags[$((_index_tags-1))]}..${tags[$((_index_tags))]} --oneline | grep "Commit of"|tac`
        _temp_output_id=`echo -e "$_temp_output_raw" | awk -F" " {'print $1'}`
        _counter=0
        for i in `echo -e "$_temp_output_id"`
        do
            if [[ $_counter == 0 ]]
            then
                _temp_output=`echo $_temp_output_raw | sed "s/$i/$i/g"`
            else    
                _temp_output=`echo $_temp_output_raw | sed "s/$i/<br>$i/g"`
            fi
            _temp_output_raw=$_temp_output
            _counter=$(( _counter + 1 ))
            done
        _notes=`echo -e "$_notes <br>$_temp_output"`
    fi
    # Show orphan commits (With no tag parent)
    # if [[ $_index_tags == $((_len_array-1)) ]]
    # then
    #      _notes=`echo -e "$_notes \n\`git log ${tags[$((_index_tags))]}..HEAD --oneline | grep "Commit of"\`"`
    # fi     
done
sed -i '/rlsnts/q' README.md
sed -i '/rlsnts/r/dev/stdin' README.md <<<"$_notes"