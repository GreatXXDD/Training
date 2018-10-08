# Training

EpcEnbS1SapProvider 是由RRC数据传送至EPCS1接口，在EPC侧实现
EpcEnbS1SapUser     是由EPCS1接口向enbRRC发送数据，在RRC侧实现

在epc-enb-s1-sap.h中声明纯虚函数virtual void DataRadioBearerSetupRequest (DataRadioBearerSetupRequestParameters params) = 0;
函数DataRadioBearerSetupRequest在enbrrc文件中实现。
在通过SetupDataRadioBearer传递RNTI bear bearID gtpteid address   这个函数很关键

LteEnbRrc::GetLogicalChannelPriority (EpsBearer bearer) 获取逻辑性到优先级
LteEnbRrc::GetLogicalChannelGroup (EpsBearer bearer) 获取逻辑信道组是不是gbr
设置逻辑行到参数

在进行LTE UE和enb附着的时候会产生默认的TCP承载，再加上QOS承载所以有2个LC、

RLC发送HOL时延计算在RLCAM/UM/... 的DoReportBufferStatus函数中

enb RRC通过LteEnbCmacSapProvider接口 在LteEnbMac::DoAddLc (LteEnbCmacSapProvider::LcInfo lcinfo, LteMacSapUser* msu)函数中，实现信令（LC BearerQOS）传递

随机接入选择序列号从小到大的顺序选择接入的UE， 一个随即接入相应RAR需要6个PRB支持，所以当在只有25PRB的下行的情况下，最多一个子帧传送4个RAR。
e.g 10个UE需要分3组进行随机接入相应，RNTI就会用到 (1,2,3,4,5,6,7,8,9,10),(11,12,13,14,15,16),(17,18)
  
