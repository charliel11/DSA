#include <Node.h>
#include <parse.h>

/*
[[2,4],[1,3],[2,4],[1,3]]
*/
TEST(NODE, cloneGraph) {
    std::string test_name = ::testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string data_text = readtxt(DATAPATH + "createGraph" + EXT);

    vector<VVIntInt> cases;
    parse(data_text, cases);

    for (auto &c : cases) {
        Node *res = createGraph(get<0>(c));
        Node *res_clone = cloneGraph(res);
        deleteGraph(res);
        deleteGraph(res_clone);
        // ASSERT_EQ(createGraph(get<0>(c)), get<1>(c));
    }
}

TEST(NODE, createGraph) {
    std::string test_name = ::testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string data_text = readtxt(DATAPATH + test_name + EXT);

    vector<VVIntInt> cases;
    parse(data_text, cases);
    for (auto &c : cases) {
        Node *res = createGraph(get<0>(c));
        deleteGraph(res);
        // ASSERT_EQ(createGraph(get<0>(c)), get<1>(c));
    }
}