#include <ros/ros.h>
#include <tutorial_topic/Int32Stamped.h>

int main(int argc, char **argv)
{
    using tutorial_topic::Int32Stamped;
    //ROSノードの初期化
    ros::init(argc, argv, "publisher");
    ros::NodeHandle nh;
    // PublishするTopicの登録
    ros::Publisher pub = nh.advertise<Int32Stamped>("number", 10);
    ros::Duration(1.0).sleep();
    //ループ間隔の設定
    ros::Rate loop_rate(1);

    //Publishする変数の定義
    Int32Stamped cnt;
    cnt.data = 0;
    cnt.header.stamp = ros::Time::now();
    //無限ループ
    while (ros::ok())
        {
            //現在のcnt変数の値を表示
            ROS_INFO("Count : %d", cnt.data);
            //cnt変数をpublish
            pub.publish(cnt);
            //cnt変数をインクリメント
            cnt.data++;
            cnt.header.stamp = ros::Time::now();
            //ループ間隔が1秒になるように待機
            loop_rate.sleep();
        }
    return 0;
}

