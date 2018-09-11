/***********************************************************************
  * Copyright (c) 2012, Baidu Inc. All rights reserved.
  * 
  * Licensed under the BSD License
  * you may not use this file except in compliance with the License.
  * You may obtain a copy of the License at
  * 
  *      license.txt
  *********************************************************************/

#ifndef _BGCC_BINARY_PROTOCOL_H_
#define _BGCC_BINARY_PROTOCOL_H_

#include "bgcc_common.h"
#include "protocol.h"
#include "nb_data_buffer.h"

namespace bgcc {

/*
 * HEAD + BODY
 * HEAD:
 * protocol(4) version(2)	protocoltype(1) reverd(1) logid(4) ticketid(4)	bodysize(4)
 * bgcP		   10			1				0					
 *
 * BODY:
 * processor_name		
 * msgType				2 byte
 * ticketid				4 byte
 * version				2 byte
 * function_name		string		
 * proxy_name			string
 *
 *
 * String	:	len+content
 * int32_t	:	4 byte	network order
 * */

extern const unsigned char bp_magic[];
extern const unsigned char bp_hb_hdr[];

#define HEAD_SIZE	20
#define LENGTH_SIZE	sizeof(int32_t)
#define MSGTYPE_LEN	2
#define TICKETID_LEN	4
#define VERSION_LEN		2
#define MAX_DEFAULT_LEN 1024


#define OFFSET_PTR(p, offset)	((p)?((char*)p+offset):NULL)
#define INT8(p) (*((int8_t*)((char*)p)))
#define UINT8(p) ((uint8_t)INT8(p))
#define INT16(p) (ntohs(*((int16_t*)((char*)p))))
#define INT32(p) (ntohl(*((int32_t*)((char*)p))))
#define INT64(p) (ntohll(*((int64_t*)((char*)p))))

#define ISHB(p) (0xff==UINT8(OFFSET_PTR(p, 7)))

#define BODY_LEN(pack_head) ((int32_t)ntohl(*(uint32_t*)(((char*)pack_head+16))))
#define	BODY_PTR(pack) ((char*)(pack)+(HEAD_SIZE))
#define BODY_LEN_PTR(pack) (BODY_PTR(pack)-LENGTH_SIZE)
#define PROCESSOR_NAME_LEN(pack_body) ((int32_t)ntohl(*(uint32_t*)pack_body))
#define PROCESSOR_NAME_PTR(pack_body) ((char*)pack_body+LENGTH_SIZE)
#define BODY_MINUS_PROCESSOR_PTR(pack_body)	\
	( PROCESSOR_NAME_PTR(pack_body)+ PROCESSOR_NAME_LEN(pack_body) )
#define BODY_MINUS_PROCESSOR_LEN(pack_body, body_len) \
	(  body_len- PROCESSOR_NAME_LEN(pack_body) - LENGTH_SIZE )

#define FUNC_NAME_OFFSET(pack_body) \
	(BODY_MINUS_PROCESSOR_PTR(pack_body)+MSGTYPE_LEN+TICKETID_LEN+VERSION_LEN)
#define FUNC_NAME_PTR(pack_body) \
	(FUNC_NAME_OFFSET(pack_body)+LENGTH_SIZE)
#define FUNC_NAME_LEN(pack_body) \
	((int32_t)ntohl(*(uint32_t*)(FUNC_NAME_OFFSET(pack_body))))

#define PROXY_NAME_OFFSET(pack_body) \
	(FUNC_NAME_PTR(pack_body)+FUNC_NAME_LEN(pack_body))
#define PROXY_NAME_PTR(pack_body)\
	(PROXY_NAME_OFFSET(pack_body)+LENGTH_SIZE)
#define PROXY_NAME_LEN(pack_body)\
	((int32_t)ntohl(*(uint32_t*)(PROXY_NAME_OFFSET(pack_body))))




    /**
     * @class BinaryProtocol 
     * @brief 实现二进制协议序列化与反序列化
     *
     * 提供数据序列化、反序列化的二进制接口。
     */

    class BinaryProtocol : public IProtocol {
    public:
        /**
         * @brief   构造函数
         * @param   transport 底层的传输层智能指针
         */
        BinaryProtocol(TransportSharedPointer transport);
        /**
         * @brief   布尔值序列化
         * @param   value 待序列化的布尔值。
         * @return  成功时返回0。出错时返回错误码。
         */
        virtual int32_t writeBool(const bool value);

        /**
         * @brief   8位整数序列化
         * @param   value 待序列化的8位整数值。
         * @return  成功时返回0。出错时返回错误码。
         */
        virtual int32_t writeByte(const int8_t value);

        /**
         * @brief   16位整数序列化
         * @param   value 待序列化的16位整数值。
         * @return  成功时返回0。出错时返回错误码。
         */
        virtual int32_t writeInt16(const int16_t value);

        /**
         * @brief   32位整数序列化
         * @param   value 待序列化的32位整数值。
         * @return  成功时返回0。出错时返回错误码。
         */
        virtual int32_t writeInt32(const int32_t value);

        /**
         * @brief   64位整数序列化
         * @param   value 待序列化的64位整数值。
         * @return  成功时返回0。出错时返回错误码。
         */
        virtual int32_t writeInt64(const int64_t value);

        /**
         * @brief   浮点数序列化
         * @param   value 待序列化的浮点数。
         * @return  成功时返回0。出错时返回错误码。
         */
        virtual int32_t writeFloat(const float value);

        /**
         * @brief   字符串序列化
         * @param   value 待序列化的字符串。
         * @return  成功时返回0。出错时返回错误码。
         */
        virtual int32_t writeString(const std::string& value);

        /**
         * @brief   二进制数据序列化
         * @param   value 待序列化的二进制数据。
         * @return  成功时返回0。出错时返回错误码。
         */
        virtual int32_t writeBinary(const void* data, const int32_t size);

        /**
         * @brief   消息序列化开始
         * @param   msgName 消息名称
         * @param   msgType 消息类型
         * @param   seqNO   消息序列号
         * @return  成功时返回0。出错时返回错误码。
         */
        virtual int32_t writeMessageBegin(
                const std::string& processor_name,
                const std::string& function_name,
                const MsgTypeID msg_type,
                const SequenceNOType seq_no);

        /**
         * @brief   消息序列化结束
         * @return  成功时返回0。出错时返回错误码。
         */
        virtual int32_t writeMessageEnd(bool tosend=true);

        /**
         * @brief   struct序列化开始
         * @param   name set名称
         * @return  成功时返回0。出错时返回错误码。
         */
        virtual int32_t writeStructBegin(const std::string& name);

        /**
         * @brief   struct序列化结束
         * @return  成功时返回0。出错时返回错误码。
         */
        virtual int32_t writeStructEnd();

        /**
         * @brief   域序列化开始
         * @param   name       域名称
         * @param   fieldType 域类型标识
         * @param   fieldId   ？待定
         * @return  成功时返回0。出错时返回错误码。
         */
        virtual int32_t writeFieldBegin(
                const std::string& name,
                const DataTypeID fieldType,
                const FieldIDType fieldId);

        /**
         * @brief   域序列化结束
         * @return  成功时返回0。出错时返回错误码。
         */
        virtual int32_t writeFieldEnd();

        /**
         * @brief   结束域序列化, 用于标识一系列域的结束
         * @return  成功时返回0。出错时返回错误码。
         */
        virtual int32_t writeFieldStop();

        /**
         * @brief   map序列化开始
         * @param   keyType 键类型标识
         * @param   valueType 值类型标识
         * @param   size 元素个数
         * @return  成功时返回0。出错时返回错误码。
         */
        virtual int32_t writeMapBegin(
                const DataTypeID keyType,
                const DataTypeID valueType,
                const int32_t size);

        /**
         * @brief   map序列化结束
         * @return  成功时返回0。出错时返回错误码。
         */
        virtual int32_t writeMapEnd();

        /**
         * @brief   list序列化开始
         * @param   elemType 元素类型标识
         * @param   size 元素个数
         * @return  成功时返回0。出错时返回错误码。
         */
        virtual int32_t writeListBegin(
                const DataTypeID elemType,
                const int32_t size);

        /**
         * @brief   list序列化结束
         * @return  成功时返回0。出错时返回错误码。
         */
        virtual int32_t writeListEnd();

        /**
         * @brief   set序列化开始
         * @param   elemType 元素类型标识
         * @param   size 元素个数
         * @return  成功时返回0。出错时返回错误码。
         */
        virtual int32_t writeSetBegin(
                const DataTypeID elemType,
                const int32_t size);

        /**
         * @brief   set序列化结束
         * @return  成功时返回0。出错时返回错误码。
         */
        virtual int32_t writeSetEnd();

        /**
         * @brief   布尔值反序列化
         * @param   value 反序列化后得到的布尔值
         * @return  成功时返回0。出错时返回错误码。
         */
        virtual int32_t readBool(char *request, int32_t request_len, bool& value);

        /**
         * @brief   8位整数反序列化
         * @param   value 反序列化后得到的8位整数
         * @return  成功时返回0。出错时返回错误码。
         */
        virtual int32_t readByte(char *request, int32_t request_len, int8_t& value);

        /**
         * @brief   16位整数反序列化
         * @param   value 反序列化后得到的16位整数
         * @return  成功时返回0。出错时返回错误码。
         */
        virtual int32_t readInt16(char *request, int32_t request_len, int16_t& value);

        /**
         * @brief   32位整数反序列化
         * @param   value 反序列化后得到的32位整数
         * @return  成功时返回0。出错时返回错误码。
         */
        virtual int32_t readInt32(char *request, int32_t request_len, int32_t& value);

        /**
         * @brief   64位整数反序列化
         * @param   value 反序列化后得到的64位整数
         * @return  成功时返回0。出错时返回错误码。
         */
        virtual int32_t readInt64(char *request, int32_t request_len, int64_t& value);

        /**
         * @brief   浮点数反序列化
         * @param   value 反序列化后得到的浮点数
         * @return  成功时返回0。出错时返回错误码。
         */
        virtual int32_t readFloat(char *request, int32_t request_len, float& value);

        /**
         * @brief   字符串反序列化
         * @param   value 反序列化后得到的字符串
         * @return  成功时返回0。出错时返回错误码。
         */
        virtual int32_t readString(char *request, int32_t request_len, std::string& value);

        /**
         * @brief   二进制数据反序列化
         * @param   value 反序列化后得到的二进制数据
         * @return  成功时返回0。出错时返回错误码。
         */
        virtual int32_t readBinary(char *request, int32_t request_len, std::string& value);

        /**
         * @brief   set反序列化开始
         * @param   elemType 反序列化后得到的set元素类型标识
         * @param   size 反序列化后得到的set元素个数
         * @return  成功时返回0。出错时返回错误码。
         */
        virtual int32_t readSetBegin(char *request, int32_t request_len, DataTypeID& elemType, int32_t& size);

        /**
         * @brief   set反序列化结束
         * @return  成功时返回0。出错时返回错误码。
         */
        virtual int32_t readSetEnd();

        /**
         * @brief   list反序列化开始
         * @param   elemType 反序列化后得到的list元素类型标识
         * @param   size 反序列化后得到的list元素个数
         * @return  成功时返回0。出错时返回错误码。
         */
        virtual int32_t readListBegin(char *request, int32_t request_len, DataTypeID& elemType, int32_t& size);

        /**
         * @brief   list反序列化结束
         * @return  成功时返回0。出错时返回错误码。
         */
        virtual int32_t readListEnd();

        /**
         * @brief   map反序列化开始
         * @param   keyType 反序列化后得到的map键类型标识
         * @param   valueType 反序列化后得到的map值类型标识
         * @param   size 反序列后得到的元素个数
         * @return  成功时返回0。出错时返回错误码。
         */
        virtual int32_t readMapBegin(
				char *request,
                int32_t request_len, 
                DataTypeID& keyType,
                DataTypeID& valueType,
                int32_t& size);

        /**
         * @brief   map反序列化结束
         * @return  成功时返回0。出错时返回错误码。
         */
        virtual int32_t readMapEnd();

        /**
         * @brief   struct反序列化开始
         * @param   name 反序列化后得到的struct名称
         * @return  成功时返回0。出错时返回错误码。
         */
        virtual int32_t readStructBegin(char *request, int32_t request_len, std::string& name);

        /**
         * @brief   struct反序列化结束
         * @return  成功时返回0。出错时返回错误码。
         */
        virtual int32_t readStructEnd();

        /**
         * @brief   消息反序列化开始
         * @param   msgName 反序列化后得到的消息名称
         * @param   msgType 反序列化后得到的消息类型
         * @param   seqNO 反序列化得到的消息序列号
         * @return  成功时返回0。出错时返回错误码。
         */
        virtual int32_t readMessageBegin(
				char **request,
                int32_t &request_len, 
                std::string& msgName,
                MsgTypeID& msgType,
                SequenceNOType& seqNO,
				ReadItem *pItem=NULL);

        /**
         * @brief   消息反序列化结束
         * @return  成功时返回0。出错时返回错误码。
         */
        virtual int32_t readMessageEnd();

        /**
         * @brief   域反序列化开始
         * @param   name 反序列化后得到的域名称
         * @param   field_type 反序列化后得到的域类型标识
         * @param   field_id ？待定
         * @return  成功时返回0。出错时返回错误码。
         */
        virtual int32_t readFieldBegin(
				char *request,
                int32_t request_len, 
                std::string& name,
                DataTypeID& fieldType,
                FieldIDType& fieldID);

        /**
         * @brief   域反序列化结束
         * @return  成功时返回0。出错时返回错误码。
         */
        virtual int32_t readFieldEnd();

        /**
         * @brief   设置本协议所对应的底层传输层智能指针对象
         * @param   transport 待设置的传输层智能指针对象
         * @return  成功时返回0。出错时返回错误码。
         */
        virtual int32_t setTransport(TransportSharedPointer transport);

        /**
         * @brief   获取本协议所对应的底层传输层智能指针对象
         * @return  传输层智能指针对象
         */
        virtual TransportSharedPointer getTransport();

        int32_t getDataCopy(void** ppdata, int32_t& size);
    
        NBDataBuffer* get_data_buffer() {
            return &_data;
        }
    private:
        /** 底层的传输层对象智能指针 */
        TransportSharedPointer _transport;
        NBDataBuffer _data;

	private:
		int32_t readBasic(char *_dstbuf, int32_t dstbuf_len, const char *srcbuf, int32_t srcbuf_len);
    };
}

#endif
