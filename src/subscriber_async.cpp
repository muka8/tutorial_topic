#include <ros/ros.h>
#include <tutorial_topic/Int32Stamped.h>
#include <mutex>
//グローバル変数の定義
static tutorial_topic::Int32Stamped g_number;
static std::mutex g_mutex;

//Topicを受信すると呼ばれるコールバック関数
void onNumberSubscribed(const tutorial_topic::Int32Stamped &msg)
{
//関数を抜けるまでmutexをlock
 std::lock_guard<std::mutex> lock(g_mutex);
//受信したTopicをコピー
 g_number = msg;
}

int main(int argc, char **argv)
{
//ROSノードの初期化
 ros::init(argc, argv, "Subscriber");
 ros::NodeHandle nh;
//SubscribeするTopicの設定をコールバック関数の登録 
 ros::Subscriber sub = nh.subscribe("number", 10, onNumberSubscribed);
//ループ間隔の設定
 ros::Rate loop_rate(1);
//AsyncSpinnerの初期化
 ros::AsyncSpinner spinner(1);
 spinner.start();
//loop
 while(ros::ok){
//mutexをlock
 g_mutex.lock();
 //受信したTopicデータの表示
 ROS_INFO("Number : %d, Time : %1f", g_number.data, g_number.header.stamp.toSec());
 //mutexをunlock
 g_mutex.unlock();
 //周期が1秒になるように待機
 loop_rate.sleep();
 }
 return 0;
}

