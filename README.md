This is a C++ project for the insight data science anomalous detection project (https://github.com/InsightDataScience/anomaly_detection),
it requires C++ 11 or above to compile and run.


The context of this problem is to build a real-time platform to analyze purchases within a social network of users, and detect any behavior that is far from the average within that social network.There are two flexible parameters in this problem:

   D: the number of degrees that defines a user's social network.(For example "friend of a friend" is Degree = 2, and "friend of a friend of a friend" represents Degree = 3)

   T: the number of consecutive purchases made by a user's social network (not including the user's own purchases)

A purchase amount is anomalous if it's more than 3 standard deviations from the mean of the last T purchases in the user's Dth degree social network. 



To resolve the anomalous detection problem, I developed the project with the following simplications:

1. The whole network can be constructed like a graph. Graph nodes are used to represent different users, and each user use an hash table to contain its direct neighbors/friends. Graph is initially constructed from history data("batch_log") and is constantly updating for new purchase/friend/unfriend events.

2. For a single user node, we use the purchase node to stand for the purchase event. Internal id rather than the timetamp of the purchase is used to recover the sequence of purchases, since the timestamp can be the same for two purchase event. We use an global id for the whole graph, which increase when there is a new purchase. 

3. Doubly linked list is used to maintain the order of purchase history for each user node. New purchase node is inserted at the head of the linked list. As we only care the latest T purchases in the users social network, we can only keep at most T purchases for a single user to save space. When there are more than T purchases, the earliest purchase node will be poped from the tail(First in First out).

4. The statistics of a current node will be evaluated only when there is a new purchase event (from "stream_log"). The function to calculate statistics first transverse the user's Dth-degree social network and return statistics by sorting out the latest T purchases from the whole network history. 

5. In principle, an alternative is to keep the "candidate" purchase history rather than its own purchase history in each node. But this requires updating the Dth-degree social network in the presence of a new purchase, so it is preferable for the case with large amount of inquiries. So this approach may not be most efficient since the scale of the history data is much greater than the stream data,    

5. Jsoncpp libraray is used to parse the script input. "/src/json/" is the directory that contains the header file, and "/src/jsoncpp.cpp" is the source file for the library. The library is compiled as other source file, which reduce the potential work of installing and linking to the library when compiling the project



The project contains the following test cases:

  Test 1:  The test case from insight data science repository;

  Test 2:  Test case when the number of candidate puchases is greater than T in Dth-degree social network.
  Test 3:  Test case when the number of candidate puchases is less than T in Dth-degree social network.
  Test 4:  Test case to check whether "stream_log" purchase updates the whole graph.

  Test 5:  Test case to check whether "stream_log" friend/unfriend updates the whole graph.
  Test 6:  Test case where the candidate purchase history is from multiple user nodes in the calculation of statistics. 

  Test 7:  Test case for the heap structure in the calculation of statistics. 

  Test 8:  Test case for invalid input

  Test 9:  Test case for large value of D, large degree of social network.

  Test 10: Test case when there is no output file.

