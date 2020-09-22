file(REMOVE_RECURSE
  "libmindspore.a"
  "libmindspore.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/mindspore.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
