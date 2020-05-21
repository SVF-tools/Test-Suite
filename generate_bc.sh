root=$(cd "$(dirname "$0")";pwd)

#check wether the test case bc folder exist 
if [ -d 'test_cases_bc' ] ; then
    echo "folder exists!"
else
    mkdir "test_cases_bc"
	cp aliascheck.h test_cases_bc/ 
fi

bc_path=$root"/test_cases_bc/"

function generate_bc(){
if [ "X$1" != 'X' ]
   then
         cd "$1"
  fi
  
  files=`ls`
for filename in $files;do
	
	if [ -d $filename ]
    	then	
		generate_bc $filename 
			
	else
	#check wether the file is cpp or c file
	if [ ${filename##*.} = 'cpp' ] || [ ${filename##*.} = 'c' ]
	 then
        file_path=$(cd "$(dirname "$filename")";pwd)
	    echo $file_path"/"$filename
        clang -c -iquote $bc_path -emit-llvm $file_path"/"$filename -o $bc_path$filename".bc" -Wno-everything
		opt -mem2reg $bc_path$filename".bc" -o $bc_path$filename".bc"
	fi
	
	fi
done
	cd ..
}

generate_bc