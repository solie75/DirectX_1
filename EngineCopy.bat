xcopy /s /y /exclude:exclude_list.txt ".\Engine\*.h" ".\External\Include\Engine"
xcopy /s /y /exclude:exclude_list.txt ".\Engine\*.fx" ".\OutputFile\bin\content\shader"