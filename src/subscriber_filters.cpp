#include <ros/ros.h>
#include <message_filters/subscriber.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <tutorial_topic/Int32Stamped.h>

using tutorial_topic::Int32Stamped;
using tutorial_topic::Int32StampedConstPtr;
//Topicを受信すると呼ばれるコールバック関数
void onNumberSubscribed(const Int32StampedConstPtr &msg1, const Int32StampedConstPtr &msg2)
{
 //受信したデータを表示
 ROS_INFO("I heard: [%d, %d]", msg1->data, msg2->data);
}

int main(int argc, char **argv)
{
	using message_filters::sync_policies::ApproximateTime;
	using message_filters::Synchronizer;
	//ROSノードの初期化
	ros::init(argc, argv, "subscriber");
	ros::NodeHandle nh;
	// message_filtersの初期化
	typedef ApproximateTime<Int32Stamped, Int32Stamped> SyncPolicy;
	message_filters::Subscriber<Int32Stamped> sub1(nh, "number1", 10);
	message_filters::Subscriber<Int32Stamped> sub2(nh, "number2", 10);
	Synchronizer<SyncPolicy> sync_msgs(SyncPolicy(10), sub1, sub2);
	sync_msgs.registerCallback(boost::bind(&onNumberSubscribed, _1, _2));
	//コールバックを待機
	ros::spin();
	return 0;
}
