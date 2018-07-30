/**
@File      GxIAPI.h
@Brief     the interface for the GxIAPI dll module. 
@Author    Software Department
@Date      2017-8-1
@Version   1.1.1708.9011
*/

#ifndef GX_GALAXY_H
#define GX_GALAXY_H


//////////////////////////////////////////////////////////////////////////
//	���Ͷ��壬�������Ͷ��ڱ�׼C��ͷ�ļ�stdint.h���ж��壬������΢��ı���ƽ̨
//	VS2010֮ǰ�İ汾�ж����������ļ�,�����ڴ���Ҫ�ض���
//////////////////////////////////////////////////////////////////////////

#if defined(_WIN32)
	#ifndef _STDINT_H 
		#ifdef _MSC_VER // Microsoft compiler
			#if _MSC_VER < 1600
				typedef __int8            int8_t;
				typedef __int16           int16_t;
				typedef __int32           int32_t;
				typedef __int64           int64_t;
				typedef unsigned __int8   uint8_t;
				typedef unsigned __int16  uint16_t;
				typedef unsigned __int32  uint32_t;
				typedef unsigned __int64  uint64_t;
			#else
				// In Visual Studio 2010 is stdint.h already included
				#include <stdint.h>
			#endif
		#else
			// Not a Microsoft compiler
			#include <stdint.h>
		#endif
	#endif 
#else
	// Linux
	#include <stdint.h>
#endif


//------------------------------------------------------------------------------
//  ����ϵͳƽ̨����
//------------------------------------------------------------------------------

#include <stddef.h>

#ifdef WIN32
	#ifndef _WIN32
		#define _WIN32
	#endif
#endif

#ifdef _WIN32
	#include <Windows.h>
	#define GX_DLLIMPORT   __declspec(dllimport)
	#define GX_DLLEXPORT   __declspec(dllexport)

	#define GX_STDC __stdcall
	#define GX_CDEC __cdecl

	#if defined(__cplusplus)
		#define GX_EXTC extern "C"
	#else
		#define GX_EXTC
	#endif
#else
	// remove the None #define conflicting with GenApi
	#undef None
	#if __GNUC__>=4
		#define GX_DLLIMPORT   __attribute__((visibility("default")))
		#define GX_DLLEXPORT   __attribute__((visibility("default")))

		#if defined(__i386__)
			#define GX_STDC __attribute__((stdcall))
			#define GX_CDEC __attribute__((cdecl))
		#else
			#define GX_STDC 
			#define GX_CDEC 
		#endif

		#if defined(__cplusplus)
			#define GX_EXTC extern "C"
		#else
			#define GX_EXTC
		#endif
	#else
		#error Unknown compiler
	#endif
#endif

#ifdef GX_GALAXY_DLL
	#define GX_DLLENTRY GX_EXTC GX_DLLEXPORT
#else
	#define GX_DLLENTRY GX_EXTC GX_DLLIMPORT
#endif

//------------------------------------------------------------------------------
//  �����붨��
//------------------------------------------------------------------------------
typedef enum GX_STATUS_LIST
{
	GX_STATUS_SUCCESS                =  0,           ///< �ɹ�
	GX_STATUS_ERROR                  = -1,           ///< ������������δ��ȷָ�����ڲ�����
	GX_STATUS_NOT_FOUND_TL           = -2,           ///< �Ҳ���TL��
	GX_STATUS_NOT_FOUND_DEVICE       = -3,           ///< �Ҳ����豸
	GX_STATUS_OFFLINE                = -4,           ///< ��ǰ�豸Ϊ����״̬
	GX_STATUS_INVALID_PARAMETER      = -5,           ///< ��Ч����,һ����ָ��ΪNULL�������IP�Ȳ�����ʽ��Ч
	GX_STATUS_INVALID_HANDLE         = -6,           ///< ��Ч���
	GX_STATUS_INVALID_CALL           = -7,           ///< ��Ч�Ľӿڵ���,רָ����ӿ��߼�����
	GX_STATUS_INVALID_ACCESS         = -8,           ///< ���ܵ�ǰ���ɷ��ʻ��豸����ģʽ����
	GX_STATUS_NEED_MORE_BUFFER       = -9,           ///< �û������buffer����:������ʱ�û�����buffersizeС��ʵ����Ҫ
	GX_STATUS_ERROR_TYPE             = -10,          ///< �û�ʹ�õ�FeatureID���ʹ��󣬱������ͽӿ�ʹ���˸����͵Ĺ�����
	GX_STATUS_OUT_OF_RANGE           = -11,          ///< �û�д���ֵԽ��
	GX_STATUS_NOT_IMPLEMENTED        = -12,          ///< ��ǰ��֧�ֵĹ���
	GX_STATUS_NOT_INIT_API           = -13,          ///< û�е��ó�ʼ���ӿ�
	GX_STATUS_TIMEOUT                = -14,          ///< ��ʱ����
}GX_STATUS_LIST;
typedef int32_t GX_STATUS;

//------------------------------------------------------------------------------
//  ֡״̬�붨��
//------------------------------------------------------------------------------
typedef enum GX_FRAME_STATUS_LIST
{
	GX_FRAME_STATUS_SUCCESS          = 0,     ///< ����֡
	GX_FRAME_STATUS_INCOMPLETE       = -1,    ///< ��֡
}GX_FRAME_STATUS_LIST;
typedef  int32_t  GX_FRAME_STATUS;

//------------------------------------------------------------------------------
//  �豸�����붨��
//------------------------------------------------------------------------------
typedef enum GX_DEVICE_CLASS_LIST
{
	GX_DEVICE_CLASS_UNKNOWN = 0,     ///< δ֪�豸����
	GX_DEVICE_CLASS_USB2    = 1,     ///< USB2.0�豸
	GX_DEVICE_CLASS_GEV     = 2,     ///< ǧ�����豸
	GX_DEVICE_CLASS_U3V     = 3,     ///< USB3.0�豸
}GX_DEVICE_CLASS_LIST;
typedef  int32_t GX_DEVICE_CLASS;

//------------------------------------------------------------------------------
//  ��������Ϣ
//------------------------------------------------------------------------------
typedef enum GX_FEATURE_MASK
{
    GX_FEATURE_TYPE_MASK           =0xF0000000,         ///������type��Ϣ
    GX_FEATURE_LEVEL_MASK          =0x0F000000,         ///������㼶��Ϣ
}GX_FEATURE_MASK;

//------------------------------------------------------------------------------
//  ���������Ͷ���
//------------------------------------------------------------------------------
typedef enum GX_FEATURE_TYPE
{
	GX_FEATURE_INT				   =0x10000000,  ///< ������
	GX_FEATURE_FLOAT               =0X20000000,  ///< ������
	GX_FEATURE_ENUM				   =0x30000000,  ///< ö��
	GX_FEATURE_BOOL				   =0x40000000,  ///< ����
	GX_FEATURE_STRING			   =0x50000000,  ///< �ַ���
	GX_FEATURE_BUFFER			   =0x60000000,  ///< buffer
	GX_FEATURE_COMMAND			   =0x70000000,  ///< ����
}GX_FEATURE_TYPE;

//------------------------------------------------------------------------------
//  �����������㼶����
//------------------------------------------------------------------------------
typedef enum GX_FEATURE_LEVEL
{
	GX_FEATURE_LEVEL_REMOTE_DEV	    =0x00000000,  ///< RemoteDevice��
	GX_FEATURE_LEVEL_TL				=0x01000000,  ///< TL��
	GX_FEATURE_LEVEL_IF             =0x02000000,  ///< Interface��	
	GX_FEATURE_LEVEL_DEV		    =0x03000000,  ///< Device��
	GX_FEATURE_LEVEL_DS			    =0x04000000,  ///< DataStream��
}GX_FEATURE_LEVEL;

//------------------------------------------------------------------------------
//  �豸�ķ��ʷ�ʽ
//------------------------------------------------------------------------------
typedef enum GX_ACCESS_MODE
{
	GX_ACCESS_READONLY      =2,        ///< ֻ����ʽ
	GX_ACCESS_CONTROL       =3,        ///< ���Ʒ�ʽ
	GX_ACCESS_EXCLUSIVE     =4,        ///< ��ռ��ʽ
}GX_ACCESS_MODE;
typedef int32_t GX_ACCESS_MODE_CMD;

//------------------------------------------------------------------------------
//  ��ǰ�豸�Ŀɷ��ʷ�ʽ
//------------------------------------------------------------------------------
typedef enum GX_ACCESS_STATUS
{
	GX_ACCESS_STATUS_UNKNOWN    = 0,   ///< �豸��ǰ״̬δ֪
	GX_ACCESS_STATUS_READWRITE  = 1,   ///< �豸��ǰ�ɶ���д
	GX_ACCESS_STATUS_READONLY   = 2,   ///< �豸��ǰֻ֧�ֶ�
	GX_ACCESS_STATUS_NOACCESS   = 3,   ///< �豸��ǰ�Ȳ�֧�ֶ����ֲ�֧��д
}GX_ACCESS_STATUS;
typedef int32_t GX_ACCESS_STATUS_CMD;

//------------------------------------------------------------------------------
//  �豸�Ĵ򿪷�ʽ
//------------------------------------------------------------------------------
typedef enum GX_OPEN_MODE
{
	GX_OPEN_SN              =0,        ///< ͨ��SN��
	GX_OPEN_IP              =1,        ///< ͨ��IP��
	GX_OPEN_MAC             =2,        ///< ͨ��MAC��
	GX_OPEN_INDEX           =3,        ///< ͨ��Index��
	GX_OPEN_USERID          =4,        ///< ͨ���û��Զ���ID��
}GX_OPEN_MODE;
typedef int32_t GX_OPEN_MODE_CMD;

typedef enum GX_FEATURE_ID
{
	//////////////////////////////////////////////////////////////////////////
	/// Զ���豸��(Remote Device Feature)
	//////////////////////////////////////////////////////////////////////////

	//---------------DeviceInfomation Section--------------------------
	GX_STRING_DEVICE_VENDOR_NAME               = 0   | GX_FEATURE_STRING | GX_FEATURE_LEVEL_REMOTE_DEV,     ///< ��������
	GX_STRING_DEVICE_MODEL_NAME                = 1   | GX_FEATURE_STRING | GX_FEATURE_LEVEL_REMOTE_DEV,     ///< �豸�ͺ�
	GX_STRING_DEVICE_FIRMWARE_VERSION          = 2   | GX_FEATURE_STRING | GX_FEATURE_LEVEL_REMOTE_DEV,     ///< �豸�̼��汾
	GX_STRING_DEVICE_VERSION                   = 3   | GX_FEATURE_STRING | GX_FEATURE_LEVEL_REMOTE_DEV,     ///< �豸�汾
	GX_STRING_DEVICE_SERIAL_NUMBER             = 4   | GX_FEATURE_STRING | GX_FEATURE_LEVEL_REMOTE_DEV,     ///< �豸���к�
	GX_STRING_FACTORY_SETTING_VERSION          = 6   | GX_FEATURE_STRING | GX_FEATURE_LEVEL_REMOTE_DEV,     ///< ���������汾
	GX_STRING_DEVICE_USERID                    = 7   | GX_FEATURE_STRING | GX_FEATURE_LEVEL_REMOTE_DEV,     ///< �û��Զ�������
	GX_INT_DEVICE_LINK_SELECTOR                = 8   | GX_FEATURE_INT    | GX_FEATURE_LEVEL_REMOTE_DEV,     ///< �豸��·ѡ��
	GX_ENUM_DEVICE_LINK_THROUGHPUT_LIMIT_MODE  = 9   | GX_FEATURE_ENUM   | GX_FEATURE_LEVEL_REMOTE_DEV,     ///< �豸��������ģʽ���ο�GX_DEVICE_LINK_THROUGHPUT_LIMIT_MODE_ENTRY
	GX_INT_DEVICE_LINK_THROUGHPUT_LIMIT        = 10  | GX_FEATURE_INT    | GX_FEATURE_LEVEL_REMOTE_DEV,     ///< �豸��·��������
	GX_INT_DEVICE_LINK_CURRENT_THROUGHPUT      = 11  | GX_FEATURE_INT    | GX_FEATURE_LEVEL_REMOTE_DEV,     ///< ��ǰ�豸�ɼ�����


	//---------------ImageFormat Section--------------------------------
	GX_INT_WIDTH_MAX                  = 1002 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,     ///< �����
	GX_INT_HEIGHT_MAX                 = 1003 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,     ///< ���߶�
	GX_INT_OFFSET_X                   = 1004 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,     ///< ˮƽƫ��
	GX_INT_OFFSET_Y                   = 1005 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,     ///< ��ֱƫ��
	GX_INT_WIDTH                      = 1006 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,     ///< ͼ����
	GX_INT_HEIGHT                     = 1007 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,     ///< ͼ��߶�
	GX_INT_BINNING_HORIZONTAL         = 1008 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,     ///< ˮƽ����Binning
	GX_INT_BINNING_VERTICAL           = 1009 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,     ///< ��ֱ����Binning
	GX_INT_DECIMATION_HORIZONTAL      = 1010 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,     ///< ˮƽ���س���
	GX_INT_DECIMATION_VERTICAL        = 1011 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,     ///< ��ֱ���س���
	GX_ENUM_PIXEL_SIZE                = 1012 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< ����λ��,�ο�GX_PIXEL_SIZE_ENTRY
	GX_ENUM_PIXEL_COLOR_FILTER        = 1013 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< Bayer��ʽ,�ο�GX_PIXEL_COLOR_FILTER_ENTRY
	GX_ENUM_PIXEL_FORMAT              = 1014 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< ���ظ�ʽ,�ο�GX_PIXEL_FORMAT_ENTRY
	GX_BOOL_REVERSE_X                 = 1015 | GX_FEATURE_BOOL | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< ˮƽ��ת
	GX_BOOL_REVERSE_Y                 = 1016 | GX_FEATURE_BOOL | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< ��ֱ��ת
	GX_ENUM_TEST_PATTERN              = 1017 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< ����ͼ,�ο�GX_TEST_PATTERN_ENTRY
	GX_ENUM_TEST_PATTERN_GENERATOR_SELECTOR = 1018 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,   ///< ����ͼԴѡ�񣬲ο�GX_TEST_PATTERN_GENERATOR_SELECTOR_ENTRY

	//---------------AcquisitionTrigger Section---------------------------
	GX_ENUM_ACQUISITION_MODE          = 3000 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< �ɼ�ģʽ,�ο�GX_ACQUISITION_MODE_ENTRY
	GX_COMMAND_ACQUISITION_START      = 3001 | GX_FEATURE_COMMAND | GX_FEATURE_LEVEL_REMOTE_DEV, ///< ��ʼ�ɼ�
	GX_COMMAND_ACQUISITION_STOP       = 3002 | GX_FEATURE_COMMAND | GX_FEATURE_LEVEL_REMOTE_DEV, ///< ֹͣ�ɼ�
	GX_INT_ACQUISITION_SPEED_LEVEL    = 3003 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,     ///< �ɼ��ٶȼ���
	GX_INT_ACQUISITION_FRAME_COUNT    = 3004 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,     ///< ��֡�ɼ�֡��
	GX_ENUM_TRIGGER_MODE              = 3005 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< ����ģʽ,�ο�GX_TRIGGER_MODE_ENTRY
	GX_COMMAND_TRIGGER_SOFTWARE       = 3006 | GX_FEATURE_COMMAND | GX_FEATURE_LEVEL_REMOTE_DEV, ///< ����
	GX_ENUM_TRIGGER_ACTIVATION        = 3007 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< ��������,�ο�GX_TRIGGER_ACTIVATION_ENTRY
	GX_ENUM_TRIGGER_SWITCH            = 3008 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< �ⴥ������,�ο�GX_TRIGGER_SWITCH_ENTRY
	GX_FLOAT_EXPOSURE_TIME            = 3009 | GX_FEATURE_FLOAT | GX_FEATURE_LEVEL_REMOTE_DEV,   ///< �ع�ʱ��
	GX_ENUM_EXPOSURE_AUTO             = 3010 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< �Զ��ع�,�ο�GX_EXPOSURE_AUTO_ENTRY
	GX_FLOAT_TRIGGER_FILTER_RAISING   = 3011 | GX_FEATURE_FLOAT | GX_FEATURE_LEVEL_REMOTE_DEV,   ///< �����ش����˲�
	GX_FLOAT_TRIGGER_FILTER_FALLING   = 3012 | GX_FEATURE_FLOAT | GX_FEATURE_LEVEL_REMOTE_DEV,   ///< �½��ش����˲�
	GX_ENUM_TRIGGER_SOURCE            = 3013 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< ����Դ,�ο�GX_TRIGGER_SOURCE_ENTRY
	GX_ENUM_EXPOSURE_MODE             = 3014 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< �ع�ģʽ���ο�GX_EXPOSURE_MODE_ENTRY
	GX_ENUM_TRIGGER_SELECTOR          = 3015 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< ��������ѡ�񣬲ο�GX_TRIGGER_SELECTOR_ENTRY
	GX_FLOAT_TRIGGER_DELAY            = 3016 | GX_FEATURE_FLOAT | GX_FEATURE_LEVEL_REMOTE_DEV,   ///< �����ӳ�
	GX_ENUM_TRANSFER_CONTROL_MODE     = 3017 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< �������ģʽ���ο�GX_TRANSFER_CONTROL_MODE_ENTRY
	GX_ENUM_TRANSFER_OPERATION_MODE   = 3018 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< �������ģʽ���ο�GX_TRANSFER_OPERATION_MODE_ENTRY
	GX_COMMAND_TRANSFER_START         = 3019 | GX_FEATURE_COMMAND | GX_FEATURE_LEVEL_REMOTE_DEV, ///< ��ʼ����
	GX_INT_TRANSFER_BLOCK_COUNT       = 3020 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,     ///< ����֡������GX_ENUM_TRANSFER_OPERATION_MODE����ΪGX_ENUM_TRANSFER_OPERATION_MODE_MULTIBLOCKģʽ��ʱ��˹��ܱ�����
	GX_BOOL_FRAMESTORE_COVER_ACTIVE   = 3021 | GX_FEATURE_BOOL | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< ֡�渲��ʹ��


	//----------------DigitalIO Section----------------------------------
	GX_ENUM_USER_OUTPUT_SELECTOR      = 4000 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,   ///< �û��Զ������ѡ��,�ο�GX_USER_OUTPUT_SELECTOR_ENTRY
	GX_BOOL_USER_OUTPUT_VALUE         = 4001 | GX_FEATURE_BOOL | GX_FEATURE_LEVEL_REMOTE_DEV,   ///< �û��Զ������ֵ
	GX_ENUM_USER_OUTPUT_MODE          = 4002 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,   ///< �û�IO���ģʽ,�ο�GX_USER_OUTPUT_MODE_ENTRY
	GX_ENUM_STROBE_SWITCH             = 4003 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,   ///< ����ƿ���,�ο�GX_STROBE_SWITCH_ENTRY
	GX_ENUM_LINE_SELECTOR             = 4004 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,   ///< ����ѡ��,�ο�GX_LINE_SELECTOR_ENTRY
	GX_ENUM_LINE_MODE                 = 4005 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,   ///< ���ŷ���,�ο�GX_LINE_MODE_ENTRY
	GX_BOOL_LINE_INVERTER             = 4006 | GX_FEATURE_BOOL | GX_FEATURE_LEVEL_REMOTE_DEV,   ///< ���ŵ�ƽ��ת
	GX_ENUM_LINE_SOURCE               = 4007 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,   ///< �������Դ,�ο�GX_LINE_SOURCE_ENTRY
	GX_BOOL_LINE_STATUS               = 4008 | GX_FEATURE_BOOL | GX_FEATURE_LEVEL_REMOTE_DEV,   ///< ����״̬
	GX_INT_LINE_STATUS_ALL            = 4009 | GX_FEATURE_INT  | GX_FEATURE_LEVEL_REMOTE_DEV,   ///< �������ŵ�״̬

	//----------------AnalogControls Section----------------------------
	GX_ENUM_GAIN_AUTO                 = 5000 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,   ///< �Զ�����,�ο�GX_GAIN_AUTO_ENTRY
	GX_ENUM_GAIN_SELECTOR             = 5001 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,   ///< ����ͨ��ѡ��,�ο�GX_GAIN_SELECTOR_ENTRY	
	GX_ENUM_BLACKLEVEL_AUTO           = 5003 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,   ///< �Զ��ڵ�ƽ,�ο�GX_BLACKLEVEL_AUTO_ENTRY
	GX_ENUM_BLACKLEVEL_SELECTOR       = 5004 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,   ///< �ڵ�ƽͨ��ѡ��,�ο�GX_BLACKLEVEL_SELECTOR_ENTRY	
	GX_ENUM_BALANCE_WHITE_AUTO        = 5006 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,   ///< �Զ���ƽ��,�ο�GX_BALANCE_WHITE_AUTO_ENTRY
	GX_ENUM_BALANCE_RATIO_SELECTOR    = 5007 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,   ///< ��ƽ��ͨ��ѡ��,�ο�GX_BALANCE_RATIO_SELECTOR_ENTRY
	GX_FLOAT_BALANCE_RATIO            = 5008 | GX_FEATURE_FLOAT | GX_FEATURE_LEVEL_REMOTE_DEV,  ///< ��ƽ��ϵ��
	GX_ENUM_COLOR_CORRECT             = 5009 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,   ///< ��ɫУ��,�ο�GX_COLOR_CORRECT_ENTRY
	GX_ENUM_DEAD_PIXEL_CORRECT        = 5010 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,   ///< ����У��,�ο�GX_DEAD_PIXEL_CORRECT_ENTRY
	GX_FLOAT_GAIN                     = 5011 | GX_FEATURE_FLOAT | GX_FEATURE_LEVEL_REMOTE_DEV,  ///< ����
	GX_FLOAT_BLACKLEVEL               = 5012 | GX_FEATURE_FLOAT | GX_FEATURE_LEVEL_REMOTE_DEV,  ///< �ڵ�ƽ

	//---------------CustomFeature Section-------------------------
	GX_INT_ADC_LEVEL                  = 6000 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< ADת������
	GX_INT_H_BLANKING                 = 6001 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< ˮƽ����
	GX_INT_V_BLANKING                 = 6002 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< ��ֱ����
	GX_STRING_USER_PASSWORD           = 6003 | GX_FEATURE_STRING | GX_FEATURE_LEVEL_REMOTE_DEV, ///< �û�����������
	GX_STRING_VERIFY_PASSWORD         = 6004 | GX_FEATURE_STRING | GX_FEATURE_LEVEL_REMOTE_DEV, ///< �û�������У������
	GX_BUFFER_USER_DATA               = 6005 | GX_FEATURE_BUFFER | GX_FEATURE_LEVEL_REMOTE_DEV, ///< �û�����������
	GX_INT_GRAY_VALUE                 = 6006 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< �����Ҷ�ֵ
	GX_ENUM_AA_LIGHT_ENVIRONMENT      = 6007 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,   ///< �Զ��ع⡢�Զ����棬���ջ�������,�ο�GX_AA_LIGHT_ENVIRMENT_ENTRY
	GX_INT_AAROI_OFFSETX              = 6008 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< �Զ����ڸ���Ȥ����X����
	GX_INT_AAROI_OFFSETY              = 6009 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< �Զ����ڸ���Ȥ����Y����
	GX_INT_AAROI_WIDTH                = 6010 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< �Զ����ڸ���Ȥ������
	GX_INT_AAROI_HEIGHT               = 6011 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< �Զ����ڸ���Ȥ����߶�
	GX_FLOAT_AUTO_GAIN_MIN            = 6012 | GX_FEATURE_FLOAT | GX_FEATURE_LEVEL_REMOTE_DEV,  ///< �Զ�������Сֵ
	GX_FLOAT_AUTO_GAIN_MAX            = 6013 | GX_FEATURE_FLOAT | GX_FEATURE_LEVEL_REMOTE_DEV,  ///< �Զ��������ֵ
	GX_FLOAT_AUTO_EXPOSURE_TIME_MIN   = 6014 | GX_FEATURE_FLOAT | GX_FEATURE_LEVEL_REMOTE_DEV,  ///< �Զ��ع���Сֵ
	GX_FLOAT_AUTO_EXPOSURE_TIME_MAX   = 6015 | GX_FEATURE_FLOAT | GX_FEATURE_LEVEL_REMOTE_DEV,  ///< �Զ��ع����ֵ
	GX_BUFFER_FRAME_INFORMATION       = 6016 | GX_FEATURE_BUFFER | GX_FEATURE_LEVEL_REMOTE_DEV, ///< ͼ��֡��Ϣ
	GX_INT_CONTRAST_PARAM             = 6017 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< �ԱȶȲ���
	GX_FLOAT_GAMMA_PARAM              = 6018 | GX_FEATURE_FLOAT | GX_FEATURE_LEVEL_REMOTE_DEV,  ///< ٤�����
	GX_INT_COLOR_CORRECTION_PARAM     = 6019 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< ��ɫУ��ϵ��
	GX_ENUM_IMAGE_GRAY_RAISE_SWITCH   = 6020 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,   ///< ͼ���������쿪��,�ο�GX_IMAGE_GRAY_RAISE_SWITCH_ENTRY
	GX_ENUM_AWB_LAMP_HOUSE            = 6021 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,   ///< �Զ���ƽ���Դ,�ο�GX_AWB_LAMP_HOUSE_ENTRY
	GX_INT_AWBROI_OFFSETX             = 6022 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< �Զ���ƽ�����Ȥ����X����
	GX_INT_AWBROI_OFFSETY             = 6023 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< �Զ���ƽ�����Ȥ����Y����
	GX_INT_AWBROI_WIDTH               = 6024 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< �Զ���ƽ�����Ȥ������
	GX_INT_AWBROI_HEIGHT              = 6025 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< �Զ���ƽ�����Ȥ����߶�

	//---------------UserSetControl Section-------------------------
	GX_ENUM_USER_SET_SELECTOR         = 7000 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< ������ѡ��,�ο�GX_USER_SET_SELECTOR_ENTRY
	GX_COMMAND_USER_SET_LOAD          = 7001 | GX_FEATURE_COMMAND | GX_FEATURE_LEVEL_REMOTE_DEV, ///< ���ز�����
	GX_COMMAND_USER_SET_SAVE          = 7002 | GX_FEATURE_COMMAND | GX_FEATURE_LEVEL_REMOTE_DEV, ///< ���������
	GX_ENUM_USER_SET_DEFAULT          = 7003 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< ����������,�ο�GX_USER_SET_DEFAULT_ENTRY


	//---------------LUT Section-------------------------
	GX_ENUM_LUT_SELECTOR             = 9000 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV, ///< ���ұ�ѡ��,�ο�GX_LUT_SELECTOR_ENTRY
	GX_BUFFER_LUT_VALUEALL           = 9001 | GX_FEATURE_BUFFER | GX_FEATURE_LEVEL_REMOTE_DEV, ///< ���ұ�����

	//---------------ChunkData Section-------------------------
	GX_BOOL_CHUNKMODE_ACTIVE         = 10001 | GX_FEATURE_BOOL | GX_FEATURE_LEVEL_REMOTE_DEV, ///< ֡��Ϣʹ��
	GX_ENUM_CHUNK_SELECTOR           = 10002 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV, ///< ֡��Ϣ��ѡ�񣬲ο�GX_CHUNK_SELECTOR_ENTRY
	GX_BOOL_CHUNK_ENABLE             = 10003 | GX_FEATURE_BOOL | GX_FEATURE_LEVEL_REMOTE_DEV, ///< ����֡��Ϣʹ��
	

	//////////////////////////////////////////////////////////////////////////
	/// ����(DataStream Feature)
	//////////////////////////////////////////////////////////////////////////
	GX_DS_INT_ANNOUNCED_BUFFER_COUNT          = 0 | GX_FEATURE_INT | GX_FEATURE_LEVEL_DS, ///< ������Buffer����
	GX_DS_INT_DELIVERED_FRAME_COUNT           = 1 | GX_FEATURE_INT | GX_FEATURE_LEVEL_DS, ///< ����֡����(������֡)
	GX_DS_INT_LOST_FRAME_COUNT                = 2 | GX_FEATURE_INT | GX_FEATURE_LEVEL_DS, ///< buffer���㵼�µĶ�֡����
	GX_DS_INT_INCOMPLETE_FRAME_COUNT          = 3 | GX_FEATURE_INT | GX_FEATURE_LEVEL_DS, ///< ���յĲ�֡����
	GX_DS_INT_STREAM_TRANSFER_SIZE            = 16 | GX_FEATURE_INT | GX_FEATURE_LEVEL_DS,  ///< �������ݿ��С
	GX_DS_INT_STREAM_TRANSFER_NUMBER_URB      = 17 | GX_FEATURE_INT | GX_FEATURE_LEVEL_DS,  ///< ����URB����


}GX_FEATURE_ID;
typedef int32_t GX_FEATURE_ID_CMD;

//------------------------------------------------------------------------------
//  �������
//------------------------------------------------------------------------------
typedef void* GX_DEV_HANDLE;               ///< �豸�����ͨ��GXOpenDevice��ȡ��ͨ���˾�����п�����ɼ�
typedef void* GX_EVENT_CALLBACK_HANDLE;    ///< �豸�¼��ص������ע���豸����¼��ص������������豸���߻ص�����
typedef void* GX_FEATURE_CALLBACK_HANDLE;  ///< �豸���Ը��»ص������ע���豸���Ը��»ص�������ʱ���ȡ

//------------------------------------------------------------------------------------
typedef enum GX_PIXEL_SIZE_ENTRY
{
	GX_PIXEL_SIZE_BPP8  = 8,
	GX_PIXEL_SIZE_BPP10 = 10,
	GX_PIXEL_SIZE_BPP12 = 12,
	GX_PIXEL_SIZE_BPP16 = 16,
	GX_PIXEL_SIZE_BPP24 = 24,
	GX_PIXEL_SIZE_BPP30 = 30,
	GX_PIXEL_SIZE_BPP32 = 32,
	GX_PIXEL_SIZE_BPP36 = 36,
	GX_PIXEL_SIZE_BPP48 = 48,
	GX_PIXEL_SIZE_BPP64 = 64,
}GX_PIXEL_SIZE_ENTRY;

typedef enum GX_PIXEL_COLOR_FILTER_ENTRY
{
	GX_COLOR_FILTER_NONE     = 0,                        ///<��
	GX_COLOR_FILTER_BAYER_RG = 1,                        ///<RG��ʽ
	GX_COLOR_FILTER_BAYER_GB = 2,                        ///<GB��ʽ
	GX_COLOR_FILTER_BAYER_GR = 3,                        ///<GR��ʽ
	GX_COLOR_FILTER_BAYER_BG = 4,                        ///<BG��ʽ
}GX_PIXEL_COLOR_FILTER_ENTRY;

#define GX_PIXEL_MONO                  ( 0x01000000 )
#define GX_PIXEL_COLOR                 ( 0x02000000 )

#define GX_PIXEL_8BIT                  ( 0x00080000 )
#define GX_PIXEL_10BIT                 ( 0x000A0000 )
#define GX_PIXEL_12BIT                 ( 0x000C0000 )
#define GX_PIXEL_16BIT                 ( 0x00100000 )
#define GX_PIXEL_24BIT                 ( 0x00180000 )
#define GX_PIXEL_30BIT                 ( 0x001E0000 )
#define GX_PIXEL_32BIT                 ( 0x00200000 )
#define GX_PIXEL_36BIT                 ( 0x00240000 )
#define GX_PIXEL_48BIT                 ( 0x00300000 )
#define GX_PIXEL_64BIT                 ( 0x00400000 )

typedef enum GX_PIXEL_FORMAT_ENTRY
{
	GX_PIXEL_FORMAT_UNDEFINED          = (0),
	GX_PIXEL_FORMAT_MONO8              = (GX_PIXEL_MONO  | GX_PIXEL_8BIT  | 0x0001),//0x1080001,
	GX_PIXEL_FORMAT_MONO8_SIGNED       = (GX_PIXEL_MONO  | GX_PIXEL_8BIT  | 0x0002),//0x1080002,
	GX_PIXEL_FORMAT_MONO10             = (GX_PIXEL_MONO  | GX_PIXEL_16BIT | 0x0003),//0x1100003,	
	GX_PIXEL_FORMAT_MONO12             = (GX_PIXEL_MONO  | GX_PIXEL_16BIT | 0x0005),//0x1100005,	
	GX_PIXEL_FORMAT_MONO14             = (GX_PIXEL_MONO  | GX_PIXEL_16BIT | 0x0025),//0x1100025,
	GX_PIXEL_FORMAT_MONO16             = (GX_PIXEL_MONO  | GX_PIXEL_16BIT | 0x0007),//0x1100007,
	GX_PIXEL_FORMAT_BAYER_GR8          = (GX_PIXEL_MONO  | GX_PIXEL_8BIT  | 0x0008),//0x1080008,               
	GX_PIXEL_FORMAT_BAYER_RG8          = (GX_PIXEL_MONO  | GX_PIXEL_8BIT  | 0x0009),//0x1080009,                
	GX_PIXEL_FORMAT_BAYER_GB8          = (GX_PIXEL_MONO  | GX_PIXEL_8BIT  | 0x000A),//0x108000A,
	GX_PIXEL_FORMAT_BAYER_BG8          = (GX_PIXEL_MONO  | GX_PIXEL_8BIT  | 0x000B),//0x108000B,
	GX_PIXEL_FORMAT_BAYER_GR10         = (GX_PIXEL_MONO  | GX_PIXEL_16BIT | 0x000C),//0x110000C,                
	GX_PIXEL_FORMAT_BAYER_RG10         = (GX_PIXEL_MONO  | GX_PIXEL_16BIT | 0x000D),//0x110000D,
	GX_PIXEL_FORMAT_BAYER_GB10         = (GX_PIXEL_MONO  | GX_PIXEL_16BIT | 0x000E),//0x110000E,
	GX_PIXEL_FORMAT_BAYER_BG10         = (GX_PIXEL_MONO  | GX_PIXEL_16BIT | 0x000F),//0x110000F,
	GX_PIXEL_FORMAT_BAYER_GR12         = (GX_PIXEL_MONO  | GX_PIXEL_16BIT | 0x0010),//0x1100010,              
	GX_PIXEL_FORMAT_BAYER_RG12         = (GX_PIXEL_MONO  | GX_PIXEL_16BIT | 0x0011),//0x1100011,
	GX_PIXEL_FORMAT_BAYER_GB12         = (GX_PIXEL_MONO  | GX_PIXEL_16BIT | 0x0012),//0x1100012,
	GX_PIXEL_FORMAT_BAYER_BG12         = (GX_PIXEL_MONO  | GX_PIXEL_16BIT | 0x0013),//0x1100013,	
	GX_PIXEL_FORMAT_BAYER_GR16         = (GX_PIXEL_MONO  | GX_PIXEL_16BIT | 0x002E),//0x110002E,                
	GX_PIXEL_FORMAT_BAYER_RG16         = (GX_PIXEL_MONO  | GX_PIXEL_16BIT | 0x002F),//0x110002F,
	GX_PIXEL_FORMAT_BAYER_GB16         = (GX_PIXEL_MONO  | GX_PIXEL_16BIT | 0x0030),//0x1100030,
	GX_PIXEL_FORMAT_BAYER_BG16         = (GX_PIXEL_MONO  | GX_PIXEL_16BIT | 0x0031),//0x1100031,	
	GX_PIXEL_FORMAT_RGB8_PLANAR        = (GX_PIXEL_COLOR | GX_PIXEL_24BIT | 0x0021),//0x2180021,
	GX_PIXEL_FORMAT_RGB10_PLANAR       = (GX_PIXEL_COLOR | GX_PIXEL_48BIT | 0x0022),//0x2300022,
	GX_PIXEL_FORMAT_RGB12_PLANAR       = (GX_PIXEL_COLOR | GX_PIXEL_48BIT | 0x0023),//0x2300023,
	GX_PIXEL_FORMAT_RGB16_PLANAR       = (GX_PIXEL_COLOR | GX_PIXEL_48BIT | 0x0024),//0x2300024,
}GX_PIXEL_FORMAT_ENTRY;

typedef enum GX_ACQUISITION_MODE_ENTRY
{
	GX_ACQ_MODE_SINGLE_FRAME = 0,                          ///<��֡ģʽ
	GX_ACQ_MODE_MULITI_FRAME = 1,                          ///<��֡ģʽ
	GX_ACQ_MODE_CONTINUOUS   = 2,                          ///<����ģʽ
}GX_ACQUISITION_MODE_ENTRY;

typedef enum GX_TRIGGER_MODE_ENTRY
{
	GX_TRIGGER_MODE_OFF = 0,                             ///< �رմ���ģʽ
	GX_TRIGGER_MODE_ON  = 1,                             ///< �򿪴���ģʽ
}GX_TRIGGER_MODE_ENTRY;

typedef enum GX_TRIGGER_SOURCE_ENTRY
{
	GX_TRIGGER_SOURCE_SOFTWARE = 0,                      ///< ����
	GX_TRIGGER_SOURCE_LINE0    = 1,                      ///< ����Դ0
	GX_TRIGGER_SOURCE_LINE1    = 2,                      ///< ����Դ1
	GX_TRIGGER_SOURCE_LINE2    = 3,                      ///< ����Դ2
	GX_TRIGGER_SOURCE_LINE3    = 4,                      ///< ����Դ3
}GX_TRIGGER_SOURCE_ENTRY;

typedef enum GX_TRIGGER_ACTIVATION_ENTRY
{
	GX_TRIGGER_ACTIVATION_FALLINGEDGE = 0,               ///< �½��ش���
	GX_TRIGGER_ACTIVATION_RISINGEDGE  = 1,               ///< �����ش���
}GX_TRIGGER_ACTIVATION_ENTRY;

typedef enum GX_TRIGGER_SWITCH_ENTRY
{
	GX_TRIGGER_SWITCH_OFF = 0,                           ///< �ر��ⴥ��
	GX_TRIGGER_SWITCH_ON  = 1,                           ///< ���ⴥ��
}GX_TRIGGER_SWITCH_ENTRY;

typedef enum GX_EXPOSURE_MODE_ENTRY
{
	GX_EXPOSURE_MODE_TIMED          = 1,                 ///< �ع�ʱ��Ĵ��������ع�ʱ��
	GX_EXPOSURE_MODE_TRIGGERWIDTH   = 2,                 ///< �����źſ�ȿ����ع�ʱ��
}GX_EXPOSURE_MODE_ENTRY;

typedef enum GX_EXPOSURE_AUTO_ENTRY
{
	GX_EXPOSURE_AUTO_OFF        = 0,                     ///< �ر��Զ��ع�
	GX_EXPOSURE_AUTO_CONTINUOUS = 1,                     ///< �����Զ��ع�
	GX_EXPOSURE_AUTO_ONCE       = 2,                     ///< �����Զ��ع�
}GX_EXPOSURE_AUTO_ENTRY;

typedef enum GX_USER_OUTPUT_SELECTOR_ENTRY
{
	GX_USER_OUTPUT_SELECTOR_OUTPUT0 = 1,                   ///<���0
	GX_USER_OUTPUT_SELECTOR_OUTPUT1 = 2,                   ///<���1
	GX_USER_OUTPUT_SELECTOR_OUTPUT2 = 4,                   ///<���2
}GX_USER_OUTPUT_SELECTOR_ENTRY;

typedef enum GX_USER_OUTPUT_MODE_ENTRY
{
	GX_USER_OUTPUT_MODE_STROBE      = 0,                   ///<�����
	GX_USER_OUTPUT_MODE_USERDEFINED = 1,                   ///<�û��Զ���
}GX_USER_OUTPUT_MODE_ENTRY;

typedef enum GX_STROBE_SWITCH_ENTRY
{
	GX_STROBE_SWITCH_OFF = 0,                            ///< �ر�����ƿ���
	GX_STROBE_SWITCH_ON  = 1,                            ///< ������ƿ���
}GX_STROBE_SWITCH_ENTRY;

typedef enum GX_GAIN_AUTO_ENTRY
{
	GX_GAIN_AUTO_OFF        = 0,                         ///< �ر��Զ�����
	GX_GAIN_AUTO_CONTINUOUS = 1,                         ///< �����Զ�����
	GX_GAIN_AUTO_ONCE       = 2,                         ///< �����Զ�����
}GX_GAIN_AUTO_ENTRY;

typedef enum GX_GAIN_SELECTOR_ENTRY
{
	GX_GAIN_SELECTOR_ALL   = 0,                          ///< ��������ͨ��
	GX_GAIN_SELECTOR_RED   = 1,                          ///< ��ͨ������
	GX_GAIN_SELECTOR_GREEN = 2,                          ///< ��ͨ������
	GX_GAIN_SELECTOR_BLUE  = 3,                          ///< ��ͨ������
}GX_GAIN_SELECTOR_ENTRY;

typedef enum GX_BLACKLEVEL_AUTO_ENTRY
{
	GX_BLACKLEVEL_AUTO_OFF        = 0,                   ///< �ر��Զ��ڵ�ƽ
	GX_BLACKLEVEL_AUTO_CONTINUOUS = 1,                   ///< �����Զ��ڵ�ƽ
	GX_BLACKLEVEL_AUTO_ONCE       = 2,                   ///< �����Զ��ڵ�ƽ
}GX_BLACKLEVEL_AUTO_ENTRY;

typedef enum GX_BLACKLEVEL_SELECTOR_ENTRY
{
	GX_BLACKLEVEL_SELECTOR_ALL   = 0,                    ///< ���кڵ�ƽͨ��
	GX_BLACKLEVEL_SELECTOR_RED   = 1,                    ///< ��ͨ���ڵ�ƽ
	GX_BLACKLEVEL_SELECTOR_GREEN = 2,                    ///< ��ͨ���ڵ�ƽ
	GX_BLACKLEVEL_SELECTOR_BLUE  = 3,                    ///< ��ͨ���ڵ�ƽ
}GX_BLACKLEVEL_SELECTOR_ENTRY;

typedef enum GX_BALANCE_WHITE_AUTO_ENTRY
{
	GX_BALANCE_WHITE_AUTO_OFF        = 0,                ///< �ر��Զ���ƽ��
	GX_BALANCE_WHITE_AUTO_CONTINUOUS = 1,                ///< �����Զ���ƽ��
	GX_BALANCE_WHITE_AUTO_ONCE       = 2,                ///< �����Զ���ƽ��
}GX_BALANCE_WHITE_AUTO_ENTRY;

typedef enum GX_BALANCE_RATIO_SELECTOR_ENTRY
{
	GX_BALANCE_RATIO_SELECTOR_RED   = 0,                   ///<��ͨ��
	GX_BALANCE_RATIO_SELECTOR_GREEN = 1,                   ///<��ͨ��
	GX_BALANCE_RATIO_SELECTOR_BLUE  = 2,                   ///<��ͨ��
}GX_BALANCE_RATIO_SELECTOR_ENTRY;

typedef enum GX_COLOR_CORRECT_ENTRY
{
	GX_COLOR_CORRECT_OFF = 0,                            ///< �ر��Զ���ɫУ��
	GX_COLOR_CORRECT_ON  = 1,                            ///< ���Զ���ɫУ��
}GX_COLOR_CORRECT_ENTRY;

typedef enum GX_DEAD_PIXEL_CORRECT_ENTRY
{
	GX_DEAD_PIXEL_CORRECT_OFF = 0,                       ///< �ر��Զ�����У��
	GX_DEAD_PIXEL_CORRECT_ON  = 1,                       ///< ���Զ�����У��
}GX_DEAD_PIXEL_CORRECT_ENTRY;

typedef enum GX_AA_LIGHT_ENVIRMENT_ENTRY
{
	GX_AA_LIGHT_ENVIRMENT_NATURELIGHT = 0,                 ///<��Ȼ��
	GX_AA_LIGHT_ENVIRMENT_AC50HZ      = 1,                 ///<50�����չ��
	GX_AA_LIGHT_ENVIRMENT_AC60HZ      = 2,                 ///<60�����չ��
}GX_AA_LIGHT_ENVIRMENT_ENTRY;

typedef enum GX_USER_SET_SELECTOR_ENTRY
{
	GX_ENUM_USER_SET_SELECTOR_DEFAULT  = 0,                 ///<Ĭ�ϲ�����
	GX_ENUM_USER_SET_SELECTOR_USERSET0 = 1,                 ///<�û�������0
}GX_USER_SET_SELECTOR_ENTRY;

typedef enum GX_IMAGE_GRAY_RAISE_SWITCH_ENTRY
{
	GX_IMAGE_GRAY_RAISE_SWITCH_OFF = 0,                     ///< ͼ���������쿪��
	GX_IMAGE_GRAY_RAISE_SWITCH_ON  = 1,                     ///< ͼ���������쿪��
}GX_IMAGE_GRAY_RAISE_SWITCH_ENTRY;

typedef enum GX_AWB_LAMP_HOUSE_ENTRY
{
	GX_AWB_LAMP_HOUSE_ADAPTIVE      = 0,                      ///< ����Ӧ��Դ
	GX_AWB_LAMP_HOUSE_D65           = 1,                      ///< ָ��ɫ��6500k
	GX_AWB_LAMP_HOUSE_FLUORESCENCE  = 2,                      ///< ָ��ӫ���
	GX_AWB_LAMP_HOUSE_INCANDESCENT  = 3,                      ///< ָ���׳��
	GX_AWB_LAMP_HOUSE_D75           = 4,                      ///< ָ��ɫ��7500k
	GX_AWB_LAMP_HOUSE_D50           = 5,                      ///< ָ��ɫ��5000k
	GX_AWB_LAMP_HOUSE_D30           = 6,                      ///< ָ��ɫ��3000k
}GX_AWB_LAMP_HOUSE_ENTRY;

typedef enum GX_TEST_PATTERN_ENTRY
{
	GX_ENUM_TEST_PATTERN_OFF                    = 0,            ///<�ر�
	GX_ENUM_TEST_PATTERN_GRAY_FRAME_RAMP_MOVING = 1,            ///<��ֹ�Ҷȵ���
	GX_ENUM_TEST_PATTERN_SLANT_LINE_MOVING      = 2,            ///<����б����
	GX_ENUM_TEST_PATTERN_VERTICAL_LINE_MOVING   = 3,            ///<����������
}GX_TEST_PATTERN_ENTRY;

typedef enum GX_TRIGGER_SELECTOR_ENTRY
{
	GX_ENUM_TRIGGER_SELECTOR_FRAME_START        = 1,               ///<�ɼ�һ֡
} GX_TRIGGER_SELECTOR_ENTRY;

typedef enum GX_LINE_SELECTOR_ENTRY
{
	GX_ENUM_LINE_SELECTOR_LINE0           = 0,               ///<����0
	GX_ENUM_LINE_SELECTOR_LINE1           = 1,               ///<����1
	GX_ENUM_LINE_SELECTOR_LINE2           = 2,               ///<����2
	GX_ENUM_LINE_SELECTOR_LINE3           = 3,               ///<����3
} GX_LINE_SELECTOR_ENTRY;

typedef enum GX_LINE_MODE_ENTRY
{
	GX_ENUM_LINE_MODE_INPUT            = 0,               ///<����
	GX_ENUM_LINE_MODE_OUTPUT           = 1,               ///<���
} GX_LINE_MODE_ENTRY;

typedef enum GX_LINE_SOURCE_ENTRY
{
	GX_ENUM_LINE_SOURCE_OFF               = 0,       ///<�ر�
	GX_ENUM_LINE_SOURCE_STROBE            = 1,       ///<�����
	GX_ENUM_LINE_SOURCE_USEROUTPUT0       = 2,       ///<�û��Զ������0
	GX_ENUM_LINE_SOURCE_USEROUTPUT1       = 3,       ///<�û��Զ������1
	GX_ENUM_LINE_SOURCE_USEROUTPUT2       = 4,       ///<�û��Զ������2
} GX_LINE_SOURCE_ENTRY;


typedef enum GX_LUT_SELECTOR_ENTRY
{
	GX_ENUM_LUT_SELECTOR_LUMINANCE             = 0,       ///<����
} GX_LUT_SELECTOR_ENTRY;

typedef enum GX_TRANSFERDELAY_MODE_ENTRY
{
	GX_ENUM_TRANSFERDELAY_MODE_OFF     = 0,       ///<���ô����ӳ�
	GX_ENUM_TRANSFERDELAY_MODE_ON      = 1,       ///<���������ӳ�
} GX_TRANSFERDELAY_MODE_ENTRY;

typedef enum GX_COVER_FRAMESTORE_MODE_ENTRY
{
	GX_ENUM_COVER_FRAMESTORE_MODE_OFF     = 0,       ///<����֡�渲��
	GX_ENUM_COVER_FRAMESTORE_MODE_ON      = 1,       ///<����֡�渲��
} GX_COVER_FRAMESTORE_MODE_ENTRY;

typedef enum GX_USER_SET_DEFAULT_ENTRY
{
	GX_ENUM_USER_SET_DEFAULT_DEFAULT      = 0,       ///<����������
	GX_ENUM_USER_SET_DEFAULT_USERSET0     = 1,       ///<�û�������0
} GX_USER_SET_DEFAULT_ENTRY;

typedef enum GX_TRANSFER_CONTROL_MODE_ENTRY
{
	GX_ENUM_TRANSFER_CONTROL_MODE_BASIC             = 0,   ///< �رմ������ģʽ
	GX_ENUM_TRANSFER_CONTROL_MODE_USERCONTROLED     = 1,   ///< �û����ƴ������ģʽ
} GX_TRANSFER_CONTROL_MODE_ENTRY;

typedef enum GX_TRANSFER_OPERATION_MODE_ENTRY
{
	GX_ENUM_TRANSFER_OPERATION_MODE_MULTIBLOCK  = 0,  ///< ָ������֡��
} GX_TRANSFER_OPERATION_MODE_ENTRY;

typedef enum GX_DS_RESEND_MODE_ENTRY
{
	GX_DS_RESEND_MODE_OFF     = 0,  ///< �ر��ش�ģʽ     
	GX_DS_RESEND_MODE_ON      = 1,  ///< �����ش�ģʽ
} GX_DS_RESEND_MODE_ENTRY;

typedef enum GX_DEVICE_LINK_THROUGHPUT_LIMIT_MODE_ENTRY
{
	GX_DEVICE_LINK_THROUGHPUT_LIMIT_MODE_OFF   = 0,   ///< �ر��豸��������ģʽ
	GX_DEVICE_LINK_THROUGHPUT_LIMIT_MODE_ON    = 1    ///< �����豸��������ģʽ
}GX_DEVICE_LINK_THROUGHPUT_LIMIT_MODE_ENTRY;

typedef enum GX_TEST_PATTERN_GENERATOR_SELECTOR_ENTRY
{
	GX_TEST_PATTERN_GENERATOR_SELECTOR_SENSOR  = 0,  ///< sensor �Ĳ���ͼ
	GX_TEST_PATTERN_GENERATOR_SELECTOR_REGION0 = 1   ///< FPGA�Ĳ���ͼ
}GX_TEST_PATTERN_GENERATOR_SELECTOR_ENTRY;


typedef enum GX_CHUNK_SELECTOR_ENTRY
{
	GX_CHUNK_SELECTOR_CHUNK_FRAME_ID     = 1,    ///< ֡��
	GX_CHUNK_SELECTOR_CHUNK_TIME_STAMP   = 2     ///< ʱ���
}GX_CHUNK_SELECTOR_ENTRY;


//------------------------------------------------------------------------------
//  �ṹ�����Ͷ���
//------------------------------------------------------------------------------

#define GX_INFO_LENGTH_8_BYTE   (8)  ///< 8�ֽ�
#define GX_INFO_LENGTH_32_BYTE  (32) ///< 32�ֽ�
#define GX_INFO_LENGTH_64_BYTE  (64) ///< 64�ֽ�
#define GX_INFO_LENGTH_128_BYTE (128)///< 128�ֽ�


typedef struct GX_FRAME_DATA
{
	GX_FRAME_STATUS		nStatus;             ///< ͼ��ķ���״̬
	void*				pImgBuf;             ///< ͼ��buffer��ַ������chunkdata��pImgBuf ����ͼ�����ݺ�֡��Ϣ���� ��
	int32_t				nWidth;              ///< ͼ��Ŀ�
	int32_t				nHeight;             ///< ͼ��ĸ�
	int32_t				nPixelFormat;        ///< ͼ���PixFormat
	int32_t				nImgSize;            ///< ͼ���С���ݴ�С����λ�ֽڣ�����chunkdata��nImgsizeΪͼ�����ݴ�С+֡��Ϣ��С��
	uint64_t			nFrameID;            ///< ͼ���֡��
	uint64_t			nTimestamp;          ///< ͼ���ʱ���
	uint64_t			nBufID;              ///< BufID
	int32_t				reserved[1];         ///< ����
}GX_FRAME_DATA;

//------------------------------------------------------------------------------
//  ��׼C API���ܺ�������
//------------------------------------------------------------------------------
#define GX_API GX_EXTC GX_STATUS GX_STDC

//------------------------------------------------------------------------
/**
\brief     ��ȡ�������Ĵ���������Ϣ
\attention ���û����������ӿ�ʧ�ܵ�ʱ�򣬿��Ե��ô˽ӿڻ�ȡ����ʧ����Ϣ����ϸ����
\param     [out] pErrorCode    �������Ĵ����룬����û������ȡ��ֵ����ô�˲������Դ�NULL
\param     [out] pszErrText    ���ش�����Ϣ��������ַ
\param     [in,out] pSize      ������Ϣ��������ַ��С����λ�ֽ�
           ���pszErrTextΪNULL��
           [out]pnSize����ʵ����Ҫ��buffer��С
           ���pszErrText��NULL��
           [in]pnSizeΪʵ�ʷ����buffer��С
           [out]pnSize����ʵ�����buffer��С
\return    GX_STATUS_SUCCESS                �����ɹ���û�з�������
           GX_STATUS_INVALID_PARAMETER      �û������ָ��ΪNULL
	   GX_STATUS_NEED_MORE_BUFFER       �û������buffer��С
	   �������������μ�GX_STATUS_LIST
*/
//------------------------------------------------------------------------
GX_API GXGetLastError             (GX_STATUS *pErrorCode, char *pszErrText, size_t *pSize);

//------------------------------------------------------------------------
/**
\brief     ��ʼ���豸�⡣
\attention ���������ӿڣ�����GXGetLastError��GXCloseLib��֮ǰ�����ȵ��ô˽ӿڣ����û�����ʹ�ÿ��ʱ�����GXCloseLib�ͷſ���Դ��
           ���֮ǰ�û��Ѿ����ù�GXInitLib��û�е���GXCloseLib�����ٴε���GXInitLib�ӿڣ��ӿڷ��سɹ���
\return    GX_STATUS_SUCCESS             �����ɹ���û�з�������
           GX_STATUS_NOT_FOUND_TL        �Ҳ���TL��
		   �������������μ�GX_STATUS_LIST
		           
*/
//------------------------------------------------------------------------
GX_API GXInitLib();

//----------------------------------------------------------------------------------
/**
\brief     �ر��豸�⣬�ͷ���Դ
\attention �ͷſ���Դ�����û�����ʹ�ÿ��ʱ����ô˽ӿڡ�
           ����û�֮ǰû�е���GXInitLib��ֱ�ӵ���GXCloseLib���ӿڷ��سɹ���
\return    GX_STATUS_SUCCESS             �����ɹ���û�з�������
           �������������μ�GX_STATUS_LIST   
*/
//----------------------------------------------------------------------------------
GX_API GXCloseLib();


//----------------------------------------------------------------------------------
/**
\brief     ö�������豸���һ�ȡ�豸����,����ǧ�����豸�˽ӿڽ���ö��ͬ�����豸
\attention �˽ӿڵ������Ǹ��¿��ڲ��豸�б��˽ӿڻ�ı���ڲ��豸�б�
           ���Ե���GXGetAllDeviceBaseInfo��GXOpenDevice֮ǰ��Ҫ���ô˽ӿڡ�
           ������û�ָ����ʱʱ���ڳɹ�ö�ٵ��豸�����������أ�������û�ָ����ʱʱ����û��ö�ٵ��豸����һֱ�ȴ���ֱ���ﵽ�û�ָ���ĳ�ʱʱ�䷵��
\param     [out]punNumDevices �����豸����
\param     [in]unTimeOut      ö�ٵĳ�ʱʱ��(��λms)��
\return    GX_STATUS_SUCCESS             �����ɹ���û�з�������
           GX_STATUS_NOT_INIT_API        û�е���GXInitLib��ʼ����
           GX_STATUS_INVALID_PARAMETER   �û������ָ��ΪNULL
           �������������μ�GX_STATUS_LIST
*/
//----------------------------------------------------------------------------------
GX_API GXUpdateDeviceList         (uint32_t* punNumDevices, uint32_t nTimeOut);


//----------------------------------------------------------------------------------
/**
\brief ͨ����Ŵ��豸
\param nDeviceIndex �豸��ţ���1��ʼ�����磺1��2��3��4...
\param phDevice �����豸���
\return GX_STATUS,����ײ���ò������쳣�������쳣���ͷ��ز�ͬ�Ĵ�����
*/
//----------------------------------------------------------------------------------
GX_API GXOpenDeviceByIndex        (uint32_t nDeviceIndex, GX_DEV_HANDLE* phDevice);   // ������


//----------------------------------------------------------------------------------
/**
\brief     ָ���豸����ر��豸
\attention �����ظ��ر�ͬһ���豸
\param     [in]hDevice ����Ҫ�رյ��豸���
\return    GX_STATUS_SUCCESS             �����ɹ���û�з�������
           GX_STATUS_NOT_INIT_API        û�е���GXInitLib��ʼ����
		   GX_STATUS_INVALID_HANDLE      �û�����Ƿ��ľ�������߹ر��Ѿ����رյ��豸
		   �������������μ�GX_STATUS_LIST  
*/
//----------------------------------------------------------------------------------
GX_API GXCloseDevice              (GX_DEV_HANDLE hDevice);

//----------------------------------------------------------------------------------
/**
\brief      ��ȡInt����ֵ�ĵ�ǰֵ
\attention  �����ǰ���ɷ��ʣ����ô˽ӿڻ᷵�ش���GX_STATUS_INVALID_ACCESS
\param [in]hDevice �豸���
\param [in]featureID ������ID
\param [out]pnValue �������ص�ǰֵ
\return    GX_STATUS_SUCCESS             �����ɹ���û�з�������
           GX_STATUS_NOT_INIT_API        û�е���GXInitLib��ʼ����
		   GX_STATUS_INVALID_HANDLE      �û�����Ƿ��ľ��
		   GX_STATUS_NOT_IMPLEMENTED     ��ǰ��֧�ֵĹ���
		   GX_STATUS_ERROR_TYPE          �û������featureID���ʹ���
		   GX_STATUS_INVALID_PARAMETER   �û������ָ��ΪNULL
		   GX_STATUS_INVALID_ACCESS      ��ǰ���ɷ���
		   �������������μ�GX_STATUS_LIST 
*/
//----------------------------------------------------------------------------------
GX_API GXGetInt				      (GX_DEV_HANDLE hDevice, GX_FEATURE_ID_CMD featureID, int64_t* pnValue);

//----------------------------------------------------------------------------------
/**
\brief      ����Int����ֵ�ĵ�ǰֵ
\attention  �����ǰ���ɷ��ʣ����ô˽ӿڻ᷵�ش���GX_STATUS_INVALID_ACCESS
\param [in]hDevice   �豸���
\param [in]featureID ������ID
\param [in]pnValue   �û����õĵ�ǰֵ
\return    GX_STATUS_SUCCESS             �����ɹ���û�з�������
           GX_STATUS_NOT_INIT_API        û�е���GXInitLib��ʼ����
		   GX_STATUS_INVALID_HANDLE      �û�����Ƿ��ľ��
		   GX_STATUS_NOT_IMPLEMENTED     ��ǰ��֧�ֵĹ���
		   GX_STATUS_ERROR_TYPE          �û������featureID���ʹ���
		   GX_STATUS_OUT_OF_RANGE        �û�����ֵԽ��
		   GX_STATUS_INVALID_ACCESS      ��ǰ���ɷ���
�������������μ�GX_STATUS_LIST 
*/
//----------------------------------------------------------------------------------
GX_API GXSetInt				      (GX_DEV_HANDLE hDevice, GX_FEATURE_ID_CMD featureID, int64_t nValue);

//----------------------------------------------------------------------------------
/**
\brief      �û����òɼ�buffer����
\param [in]hDevice         �豸���
\param [in]nBufferNum      �û����õ�buffer����
\return     GX_STATUS_SUCCESS             �����ɹ���û�з�������
			GX_STATUS_NOT_INIT_API        û�е���GXInitLib��ʼ����
			GX_STATUS_INVALID_HANDLE      �û�����Ƿ��ľ��
			GX_STATUS_INVALID_PARAMETER    ���������Ч
			����û�к��ǵ��ģ��������Ĵ��������μ�GX_STATUS_LIST

*/
//----------------------------------------------------------------------------------
GX_API GXSetAcqusitionBufferNumber(GX_DEV_HANDLE hDevice, uint64_t nBufferNum);


//----------------------------------------------------------------------------------
/**
\brief      ����
\param [in]hDevice     �豸���
\return    GX_STATUS_SUCCESS             �����ɹ���û�з�������
           GX_STATUS_NOT_INIT_API        û�е���GXInitLib��ʼ����
		   GX_STATUS_INVALID_HANDLE      �û�����Ƿ��ľ��
		   GX_STATUS_INVALID_PARAMETER   �û�����ָ��ΪNULL
		   �������������μ�GX_STATUS_LIST 
*/
//----------------------------------------------------------------------------------
GX_API GxStreamOn  (GX_DEV_HANDLE hDevice);

//----------------------------------------------------------------------------------
/**
\brief      ��ȡһ��ͼ����ͼ������ɺ���Ҫ����GxQBuf�ӿڣ�����ɼ����޷�����
\param [in]  hDevice        �豸���
\param [out] ppFrameData   ͼ�����ݣ������������ʧ�ܣ�ͼ����������Ч��
\param [in]  nTimeOut      ��ʱʱ��(��λms)
\return    GX_STATUS_SUCCESS             �����ɹ���û�з�������
           GX_STATUS_NOT_INIT_API        û�е���GXInitLib��ʼ����
		   GX_STATUS_INVALID_HANDLE      �û�����Ƿ��ľ��
		   GX_STATUS_INVALID_PARAMETER   �û�����ָ��ΪNULL
		   �������������μ�GX_STATUS_LIST 
*/
//----------------------------------------------------------------------------------
GX_API GxDQBuf  (GX_DEV_HANDLE hDevice, GX_FRAME_DATA **ppFrameData, uint32_t nTimeOut);

//----------------------------------------------------------------------------------
/**
\brief      ��ͼ������Buf�Ż�GxIAPI�⣬�������ڲɼ�
\param [in]  hDevice        �豸���
\param [out] pFrameData     ͼ������Buf
\return    GX_STATUS_SUCCESS             �����ɹ���û�з�������
           GX_STATUS_NOT_INIT_API        û�е���GXInitLib��ʼ����
		   GX_STATUS_INVALID_HANDLE      �û�����Ƿ��ľ��
		   GX_STATUS_INVALID_PARAMETER   �û�����ָ��ΪNULL
		   �������������μ�GX_STATUS_LIST 
*/
//----------------------------------------------------------------------------------
GX_API GxQBuf  (GX_DEV_HANDLE hDevice,GX_FRAME_DATA *pFrameData);

//----------------------------------------------------------------------------------
/**
\brief      ͣ��
\param [in]hDevice     �豸���
\return    GX_STATUS_SUCCESS             �����ɹ���û�з�������
           GX_STATUS_NOT_INIT_API        û�е���GXInitLib��ʼ����
		   GX_STATUS_INVALID_HANDLE      �û�����Ƿ��ľ��
		   GX_STATUS_INVALID_PARAMETER   �û�����ָ��ΪNULL
		   �������������μ�GX_STATUS_LIST 
*/
//----------------------------------------------------------------------------------
GX_API GxStreamOff  (GX_DEV_HANDLE hDevice);


//----------------------------------------------------------------------------------
/**
\brief      ���û�ָ���Ĵ�����ֵ
\param [in]hDevice         �豸���
\param [in]ui64Address     �Ĵ�����ַ
\param [out]pBuffer        ���ؼĴ�����ֵ������ΪNULL
\param [in, out]piSize     [in]�û������Buffer��С
                           [out]�ɹ���ȡ�Ĵ�����ֵ�󣬷���ʵ�ʴ�С
\return     GX_STATUS_SUCCESS             �����ɹ���û�з�������
			GX_STATUS_NOT_INIT_API        û�е���GXInitLib��ʼ����
			GX_STATUS_INVALID_HANDLE      �û�����Ƿ��ľ��
			����û�к��ǵ��ģ��������Ĵ��������μ�GX_STATUS_LIST

*/
//----------------------------------------------------------------------------------
GX_API GXReadRemoteDevicePort(GX_DEV_HANDLE hDevice, uint64_t ui64Address, void *pBuffer, size_t *piSize);


//----------------------------------------------------------------------------------
/**
\brief      ���û�ָ���ļĴ�����д���û�����������
\param [in]hDevice         �豸���
\param [in]ui64Address     �Ĵ�����ַ
\param [in]pBuffer         ���ؼĴ�����ֵ������ΪNULL
\param [in, out]piSize     [in]�û�Ҫд���Buffer����
                           [out]����ʵ��д��Ĵ����ĳ���
\return     GX_STATUS_SUCCESS             �����ɹ���û�з�������
			GX_STATUS_NOT_INIT_API        û�е���GXInitLib��ʼ����
			GX_STATUS_INVALID_HANDLE      �û�����Ƿ��ľ��
			����û�к��ǵ��ģ��������Ĵ��������μ�GX_STATUS_LIST

*/
//----------------------------------------------------------------------------------
GX_API GXWriteRemoteDevicePort(GX_DEV_HANDLE hDevice, uint64_t ui64Address, const void *pBuffer, size_t *piSize);

#endif  //GX_GALAXY_H
