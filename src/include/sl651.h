#ifndef H_SL651
#define H_SL651

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <memory.h>
#include <stdbool.h>

#include "class.h"
#include "bytebuffer.h"

/**
 *  报文帧控制字符定义 
 */
//SOH(start of header)
#define SOH_ASCII 0x01 //ASCII字符编码报文帧起始
#define SOH_HEX 0x7E7E //HEX/BCD编码报文帧起始
//STX (start of text)
#define STX 0x02 //传输正文起始
//SYN (synchronous idle)
#define SYN 0x16 //多包传输正文起始
//ETX (end of text)
#define ETX 0x03 //报文结束，后续无报文
//ETB (end of transmission block)
#define ETB 0x17 //报文结束，后续有报文
//ENQ (enquiry)
#define ENQ 0x05 //询问
//EOT (end of transmission)
#define EOT 0x04 //传输结束，退出
//ACK (acknowledge)
#define ACK 0x06 //肯定确认，继续发送
//NAK (negative acknowledge)
#define NAK 0x15 //否定应答，反馈重发
//ESC (escape)
#define ESC 0x1b //传输结束，终端保持在线

    enum StationCategory_HEX
    {
        // 降水  P
        RAIN_STATION = 0x50,
        // 河道  H
        RIVER_STATION = 0x48,
        // 水库/湖泊 K
        RESERVOIR_STATION = 0x4B,
        // 闸坝  Z
        DAM_STATION = 0x5A,
        // 泵站  D
        PUMPING_STATION = 0x44,
        // 潮汐  T
        TIDE_STATION = 0x54,
        // 墒情  M
        SOIL_MOISTURE_STAION = 0x4D,
        // 地下水 G
        GROUNDWATER_STATION = 0x47,
        // 水质  Q
        WATER_QUALITY_STATION = 0x51,
        // 取水口 I
        WATER_INTAKE_STATION = 0x49,
        // 排水口 O
        DRIAN_STATION = 0x4F
    };

    enum FunctionCode
    {
        // 链路维持报
        KEEPALIVE = 0x2F,
        // 试试报
        TEST = 0x30,
        // 均匀时段水文信息报
        EVEN_TIME,
        // 遥测站定时报
        INTERVAL,
        // 遥测站加报报
        ADDED,
        // 遥测站小时报
        HOUR,
        // 遥测站人工置数报
        ARTIFICIAL,
        // 遥测站图片报 或 中心站查询遥测站图片采集信息
        PICTURE,
        // 中心站查询遥测站实时数据
        QUERY_REALTIME,
        // 中心站查询遥测站人工置数
        QUERY_ARTIFICIAL,
        // 中心站查询遥测站指定要素数据
        QUERY_ELEMENT,
        // 中心站修改遥测站基本配置表
        MODIFY_BASIC_CONFIG = 0x40,
        // 中心站读取遥测站基本配置表/遥测站自报基本配置表
        BASIC_CONFIG,
        // 中心站修改遥测站运行参数配置表
        MODIFY_RUNTIME_CONFIG,
        // 中心站读取遥测站运行参数配置表/遥测站自报运行参数配置表
        RUNTIME_CONFIG,
        // 查询水泵电机实时工作数据
        QUERY_PUMPING_REALTIME,
        // 查询遥测终端软件版本
        QUERY_SOFTWARE_VERSION,
        // 查询遥测站状态和报警信息
        QUERY_STATUS,
        // 初始化固态存储数据
        INIT_STORAGE,
        // 恢复终端出厂设置
        RESET,
        // 修改密码
        CHANGE_PASSWORD,
        // 设置遥测站时钟
        SET_CLOCK,
        // 设置遥测终端IC卡状态
        SET_IC,
        // 控制水泵开关命令/水泵状态信息自报
        PUMPING_SWITCH,
        // 控制阀门开关命令/阀门状态信息自报
        VALVE_SWITCH,
        // 控制闸门开关命令/闸门状态信息自报
        GATE_SWITCH,
        // 水量定值控制命令
        WATER_VOLUME_SETTING,
        // 中心站查询遥测站事件记录
        QUERY_LOG,
        // 中心站查询遥测站时钟
        QUERY_CLOCK
    };

#define ELEMENT_IDENTIFER_LEN 2
#define ELEMENT_IDENTIFER_LEADER_LEN 1
#define NUMBER_ELEMENT_LEN_OFFSET 3
#define NUMBER_ELEMENT_PRECISION_MASK 0x07 // 00000111

    /* 标识符引导符*/
    enum IdentifierLeader
    {
        /* 
        * 特殊标识符，单独解析 
        * F0 - FD && 04 && 05 && 45
        */
        // 观测时间引导符
        DATETIME = 0xF0,
        // 遥测站编码引导符
        ADDRESS = 0xF1,
        // 人工置数
        ARTIFICIAL_IL = 0xF2,
        // 图片信息
        PICTURE_IL = 0xF3,
        // 1小时内每5min时段雨量
        DRP5MIN = 0xF4,
        // 1小时内每5min间隔相对水位1, 以下相同
        RELATIVE_WATER_LEVEL_5MIN1 = 0xF5,
        RELATIVE_WATER_LEVEL_5MIN2 = 0xF6,
        RELATIVE_WATER_LEVEL_5MIN3 = 0xF7,
        RELATIVE_WATER_LEVEL_5MIN4 = 0xF8,
        RELATIVE_WATER_LEVEL_5MIN5 = 0xF9,
        RELATIVE_WATER_LEVEL_5MIN6 = 0xFA,
        RELATIVE_WATER_LEVEL_5MIN7 = 0xFB,
        RELATIVE_WATER_LEVEL_5MIN8 = 0xFC,
        // 流速批量数据
        FLOW_RATE_DATA = 0xFD,
        // 时间步长码
        TIME_STEP_CODE = 0x04,
        // 时段长，降水，引排水，抽水历时
        DURATION_OF_XX = 0x05,
        // 遥测站状态及报警信息
        STATION_STATUS = 0x45,
        // 用户自定义引导符，暂不支持
        CUSTOM_IDENTIFIER = 0xFF
    };

    // enum DataType
    // {

    // };

    // Package Struct
    // #pragma pack(1)
    /* 遥测站地址 */
    typedef struct
    {
        /**
         * A5 == 0, A4-A1 为BCD码， 组成地址
         * A5 != 0, A5-A3 BCD码，为行政区划；A2A1 HEX 为一个short值
         */
        uint8_t A5;
        uint8_t A4;
        uint8_t A3;
        uint8_t A2;
        uint8_t A1;
        // 当 A5 非 0 时，A2 A1 A0 组成一个自定义地址，为BCD码，从原始的 A2A1 HEX 转来
        uint8_t A0;
    } RemoteStationAddr;
#define A5_HYDROLOGICAL_TELEMETRY_STATION 0
#define REMOTE_STATION_ADDR_LEN 5

    /* 中心站地址/遥测站地址组合 */
    typedef struct
    {
        uint8_t centerAddr;
        RemoteStationAddr stationAddr;
    } UpAddr;

    typedef struct
    {
        uint8_t centerAddr;
        RemoteStationAddr stationAddr;
    } DownAddr;

    typedef union {
        UpAddr upAddr;
        DownAddr downAddr;
    } AddrPair;

    typedef enum
    {
        Up,
        Down
    } Direction;

    typedef struct
    {
        // 6字节BCD码
        uint8_t year;
        uint8_t month;
        uint8_t day;
        uint8_t hour;
        uint8_t minute;
        uint8_t second;
    } DateTime;

#define DATETIME_LEN 6

    typedef struct
    {
        uint16_t count;
        uint8_t seq;
    } Sequence;

    /* Head */
    typedef struct
    {
        Direction direction;
        uint16_t soh;
        AddrPair addrPair;
        uint16_t pwd;
        uint8_t funcCode;
        uint16_t len;
        uint8_t stxFlag;
        // if stxFlag == SNY
        Sequence seq;
    } Head;

#define PACKAGE_HEAD_STX_LEN 14
#define PACKAGE_HEAD_SNY_LEN 17

    // oop
#define Head_ctor(ptr_)
#define Head_dtor(ptr_)
    // "AbstractorClass" Element
    struct ElementVtbl; /* forward declaration */
    typedef struct
    {
        struct ElementVtbl const *vptr;
        uint8_t identifierLeader;
        uint8_t dataDef;
    } Element;

    typedef struct ElementVtbl
    {
        // pure virtual
        bool (*encode)(Element const *const me, ByteBuffer *const hexBuff);
        bool (*decode)(Element *const me, ByteBuffer *const hexBuff);
        size_t (*size)(Element const *const me);
    } ElementVtbl;

    void Element_ctor(Element *me, uint8_t identifierLeader, uint8_t dataDef);
#define Element_dtor(ptr_) // empty implements
    // "AbstractorClass" Element END

    // RemoteStationAddrElement
    typedef struct
    {
        // it is fixed value, 0xF1F1
        Element super;
        RemoteStationAddr stationAddr;
    } RemoteStationAddrElement;
    void RemoteStationAddrElement_ctor(RemoteStationAddrElement *const me);
#define RemoteStationAddrElement_dtor(ptr_) // empty implements
    // RemoteStationAddrElement END

    // ObserveTimeElement
    typedef struct
    {
        // it is fixed value, 0xF1F1
        Element super;
        DateTime observeTime;
    } ObserveTimeElement;

    void ObserveTimeElement_ctor(ObserveTimeElement *const me);
#define ObserveTimeElement_dtor(ptr_) // empty implements
    // ObserveTimeElement END

    typedef struct
    {
        uint16_t seq;
        DateTime sendTime;
        RemoteStationAddrElement stationAddrElement;
        uint8_t stationCategory;
        ObserveTimeElement observeTimeElement;
    } UplinkMessageHead;

    typedef struct
    {
        uint16_t seq;
        DateTime sendTime;
        RemoteStationAddrElement stationAddrElement;
    } DownlinkMessageHead;

    typedef struct
    {
        uint8_t etxFlag;
        uint16_t crc;
    } Tail;

#define PACKAGE_TAIL_LEN 3

    // "AbstractClass" Package
    struct PackageVtbl; /* forward declaration */
    typedef struct
    {
        struct PackageVtbl const *vptr; /* <== Package's Virtual Pointer */
        Head *head;
        Tail *tail;
    } Package;

    /* Package's virtual table */
    typedef struct PackageVtbl
    {
        // pure virtual
        bool (*encode)(Package const *const me, ByteBuffer *const hexBuff);
        bool (*decode)(Package *const me, ByteBuffer *const hexBuff);
        size_t (*size)();
    } PackageVtbl;

    /* Package Construtor & Destrucor */
    void Package_ctor(Package *const me, Head *head);
    /* Public methods */
    bool Package_EncodeHead(Package const *const me, ByteBuffer *const hexBuff);
    bool Package_EncodeTail(Package const *const me, ByteBuffer *const hexBuff);
    bool Package_DecodeHead(Package *const me, ByteBuffer *const hexBuff);
    bool Package_DecodeTail(Package *const me, ByteBuffer *const hexBuff);
    /* Public Helper*/
#define PACAKAGE_UPCAST(ptr_) ((Package *)(ptr_))
#define Package_dtor(ptr_)
#define Package_Direction(me_) (PACAKAGE_UPCAST(me_)->head->direction)
    // "AbstractClass" Package END

    // "Basic" LinkMessage
    typedef struct
    {
        Package super;
        uint16_t elementCount;
        Element *elements[0];
        Element *elementCursor;
    } LinkMessage;

    /* LinkMessage Construtor & Destrucor */
    void LinkMessage_ctor(LinkMessage *const me, Head *head, uint16_t elementCount);
    void LinkMessage_dtor(LinkMessage *const me);
    /* Public methods */
    bool LinkMessage_EncodeElements(LinkMessage const *const me, ByteBuffer *const hexBuff);
    bool LinkMessage_DecodeElements(LinkMessage *const me, ByteBuffer *const hexBuff);
    bool LinkMessage_PutElement(LinkMessage *const me, uint16_t index, Element *element);
    bool LinkMessage_SetElement(LinkMessage *const me, uint16_t index, Element *element);
    Element *LinkMessage_GetElement(LinkMessage const *const me, uint16_t index);
    /* Public Helper*/
#define LINKMESSAGE_UPCAST(ptr_) ((Package *)(ptr_))
#define LinkMessage_ElementCount(me_) (LINKMESSAGE_UPCAST(me_)->elementCount)
#define LinkMessage_rewind(me_) (LINKMESSAGE_UPCAST(me_)->elementCursor = 0)
    // "Basic" LinkMessage END

    // "AbstractUpClass" UplinkMessage
    typedef struct
    {
        LinkMessage super;
        UplinkMessageHead *messageHead;
    } UplinkMessage;

    /* UplinkMessage Construtor & Destrucor */
    void UplinkMessage_ctor(UplinkMessage *const me, Head *head, UplinkMessageHead *upLinkHead, uint16_t elementCount);
    void UplinkMessage_dtor(UplinkMessage *const me);
    /* Public methods */
    bool UplinkMessage_EncodeHead(UplinkMessage const *const me, ByteBuffer *const hexBuff);
    // void UplinkMessage_EncodeTail(UplinkMessage const *const me, ByteBuffer* hexBuff, size_t len);
    bool UplinkMessage_DecodeHead(UplinkMessage const *me, ByteBuffer *const hexBuff);
    // void UplinkMessage_DecodeTail(UplinkMessage const *me, ByteBuffer* hexBuff, size_t len);
    // "AbstractUpClass" UplinkMessage END

    // "AbstractUpClass" DownlinkMessage
    typedef struct
    {
        LinkMessage super;
        DownlinkMessageHead *messageHead;
    } DownlinkMessage;

    /* DownlinkMessage Construtor  & Destrucor */
    void DownlinkMessage_ctor(DownlinkMessage *const me, Head *head, DownlinkMessageHead *downLinkHead, uint16_t elementCount);
    void DownlinkMessage_dtor(DownlinkMessage *const me);
    /* Public methods */
    bool DownlinkMessage_EncodeHead(DownlinkMessage const *const me, ByteBuffer *const hexBuff);
    // void DownlinkMessage_EncodeTail(DownlinkMessage const *const me, ByteBuffer* hexBuff, size_t len);
    bool DownlinkMessage_DecodeHead(DownlinkMessage const *me, ByteBuffer *const hexBuff);
    // void DownlinkMessage_DecodeTail(DownlinkMessage const *me, ByteBuffer* hexBuff, size_t len);
    // "AbstractUpClass" DownlinkMessage END

    // Elements
    // Util Functions.
    static bool inline isNumberElement(uint8_t identifierLeader)
    {
        return identifierLeader >= 0x01 && identifierLeader <= 0x75 &&
               identifierLeader != TIME_STEP_CODE &&
               identifierLeader != STATION_STATUS &&
               identifierLeader != DURATION_OF_XX;
    }

    Element *decodeElement(ByteBuffer *const hexBuff);

    // Element Class
    // PictureElement
    typedef struct
    {
        Element super;
        ByteBuffer *buff;
    } PictureElement;

    void PictureElement_ctor(PictureElement *const me);
    void PictureElement_dtor(PictureElement *const me);
    // PictureElement END

    // DRP5MINElement
    typedef struct
    {
        Element super;
        ByteBuffer *buff;
    } DRP5MINElement;

    void DRP5MINElement_ctor(DRP5MINElement *const me);
    void DRP5MINElement_dtor(DRP5MINElement *const me);
    uint8_t DRP5MINElement_ValueAt(DRP5MINElement *const me, uint8_t index, float *val);

#define DRP5MIN_LEN 12
#define DRP5MIN_DATADEF 0x60
    // DRP5MINElement END

    // FlowRateDataElement
    typedef struct
    {
        Element super;
        ByteBuffer *buff;
    } FlowRateDataElement;

    void FlowRateDataElement_ctor(FlowRateDataElement *const me);
    void FlowRateDataElement_dtor(FlowRateDataElement *const me);
#define FLOW_RATE_DATA_DATADEF 0xF6
    // FlowRateDataElement END

    // ArtificialElement
    typedef struct
    {
        Element super;
        ByteBuffer *buff;
    } ArtificialElement;

    void ArtificialElement_ctor(ArtificialElement *const me);
    void ArtificialElement_dtor(ArtificialElement *const me);
    // ArtificialElement END

    // RelativeWaterLevelElement
    typedef struct
    {
        Element super;
        ByteBuffer *buff;
    } RelativeWaterLevelElement;

    void RelativeWaterLevelElement_ctor(RelativeWaterLevelElement *const me, uint8_t identifierLeader);
    void RelativeWaterLevelElement_dtor(RelativeWaterLevelElement *const me);
    uint8_t RelativeWaterLevelElement_ValueAt(RelativeWaterLevelElement *const me, uint8_t index, float *val);

#define RELATIVE_WATER_LEVEL_LEN 24
#define RELATIVE_WATER_LEVEL_5MIN1_DATADEF 0xC0
    // RelativeWaterLevelElement END

    // TimeStepCodeElement
    typedef struct
    {
        // 3字节BCD码
        uint8_t day;
        uint8_t hour;
        uint8_t minute;
    } TimeStepCode;

    typedef struct
    {
        // it is fixed value, 0x0418
        Element super;
        TimeStepCode timeStepCode;
    } TimeStepCodeElement;

    void TimeStepCodeElement_ctor(TimeStepCodeElement *const me);
#define TimeStepCodeElement_dtor(ptr_) // empty implements
#define TIME_STEP_CODE_LEN 3
#define TIME_STEP_CODE_DATADEF 0x18
    // TimeStepCodeElement END

    // StationStatusElement
    typedef struct
    {
        // it is fixed value, 0x0418
        Element super;
        uint32_t status;
    } StationStatusElement;

    void StationStatusElement_ctor(StationStatusElement *const me);
    uint8_t StationStatusElement_StatusAt(StationStatusElement const *const me, uint8_t index);
#define StationStatusElement_dtor(ptr_) // empty implements
#define STATION_STATUS_LEN 4
#define STATION_STATUS_DATADEF 0x20
    // StationStatusElement END

    // DurationElement
    typedef struct
    {
        // it is fixed value, 0x05 ?
        Element super;
        uint8_t hour;
        uint8_t minute;
    } DurationElement;

    void DurationElement_ctor(DurationElement *const me);
#define DurationElement_dtor(ptr_)  // empty implements
#define DURATION_OF_XX_LEN 5        // 5 字节 ASCII OR 1BCD + . + 1BCD = 3?
#define DURATION_OF_XX_DATADEF 0x28 // 同上  0x18?
    // StationStatusElement END

    // All NumberElement
    typedef struct
    {
        Element super;
        ByteBuffer *buff;
    } NumberElement;

    void NumberElement_ctor(NumberElement *const me, uint8_t identifierLeader, uint8_t dataDef);
    void NumberElement_dtor(NumberElement *const me);
    uint8_t NumberElement_GetFloat(NumberElement *const me, float *val);
    uint8_t NumberElement_GetInteger(NumberElement *const me, uint64_t *val);
    // All NumberElement END
    typedef struct
    {
        Element super;
        uint8_t extIdentifier;
    } ExtendElement;

    typedef struct
    {
        NumberElement super;
        uint8_t extIdentifier;
    } ExtendNumberElement;

    // Elements END
    // #pragma pack()
#ifdef __cplusplus
}
#endif
#endif