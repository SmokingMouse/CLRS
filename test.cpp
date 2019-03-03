#include"GoogleTest/Disjoined_Set_Test.h"
#include"GoogleTest/MST_Test.h"
#include"GoogleTest/Sort_Test.h"
#include"GoogleTest/Select_Test.h"
#include"GoogleTest/Hash_Table_Test.h"
#include"GoogleTest/String_Matching_Test.h"
#include"GoogleTest/RBTree_Test.h"

int main(int argc,char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}