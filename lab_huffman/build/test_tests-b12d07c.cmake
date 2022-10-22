add_test( test_remove_smallest /workspaces/CS225/release-f22/lab_huffman/build/test test_remove_smallest  )
set_tests_properties( test_remove_smallest PROPERTIES WORKING_DIRECTORY /workspaces/CS225/release-f22/lab_huffman/build)
add_test( test_encoder_binary /workspaces/CS225/release-f22/lab_huffman/build/test test_encoder_binary  )
set_tests_properties( test_encoder_binary PROPERTIES WORKING_DIRECTORY /workspaces/CS225/release-f22/lab_huffman/build)
add_test( test_encoder_binary2 /workspaces/CS225/release-f22/lab_huffman/build/test test_encoder_binary2  )
set_tests_properties( test_encoder_binary2 PROPERTIES WORKING_DIRECTORY /workspaces/CS225/release-f22/lab_huffman/build)
add_test( test_encoder_writetree /workspaces/CS225/release-f22/lab_huffman/build/test test_encoder_writetree  )
set_tests_properties( test_encoder_writetree PROPERTIES WORKING_DIRECTORY /workspaces/CS225/release-f22/lab_huffman/build)
add_test( test_encoder_writetree2 /workspaces/CS225/release-f22/lab_huffman/build/test test_encoder_writetree2  )
set_tests_properties( test_encoder_writetree2 PROPERTIES WORKING_DIRECTORY /workspaces/CS225/release-f22/lab_huffman/build)
add_test( test_decode /workspaces/CS225/release-f22/lab_huffman/build/test test_decode  )
set_tests_properties( test_decode PROPERTIES WORKING_DIRECTORY /workspaces/CS225/release-f22/lab_huffman/build)
add_test( test_decode2 /workspaces/CS225/release-f22/lab_huffman/build/test test_decode2  )
set_tests_properties( test_decode2 PROPERTIES WORKING_DIRECTORY /workspaces/CS225/release-f22/lab_huffman/build)
add_test( test_decode_readtree /workspaces/CS225/release-f22/lab_huffman/build/test test_decode_readtree  )
set_tests_properties( test_decode_readtree PROPERTIES WORKING_DIRECTORY /workspaces/CS225/release-f22/lab_huffman/build)
add_test( test_decode_readtree2 /workspaces/CS225/release-f22/lab_huffman/build/test test_decode_readtree2  )
set_tests_properties( test_decode_readtree2 PROPERTIES WORKING_DIRECTORY /workspaces/CS225/release-f22/lab_huffman/build)
add_test( test_the_works /workspaces/CS225/release-f22/lab_huffman/build/test test_the_works  )
set_tests_properties( test_the_works PROPERTIES WORKING_DIRECTORY /workspaces/CS225/release-f22/lab_huffman/build)
set( test_TESTS test_remove_smallest test_encoder_binary test_encoder_binary2 test_encoder_writetree test_encoder_writetree2 test_decode test_decode2 test_decode_readtree test_decode_readtree2 test_the_works)
