/*
 SmsFilterScript v1.1
*/

grammar smsfs;


options{
  output=AST;
  language=C;
  ASTLabelType=pANTLR3_BASE_TREE;
}


tokens {

	// While lists
	SCCP_GT_CALLED_WL			= 'SCCP.GT_CALLED.WL';
	SCCP_GT_CALLING_WL			= 'SCCP.GT_CALLING.WL';
	MAP_SCOA_WL				= 'MAP.SCOA.WL';
	MAP_SCDA_WL				= 'MAP.SCDA.WL';

	// SMPP specific
	SMPP_IP_SOURCE				= 'SMPP.IP.SOURCE';
	SMPP_IP_DESTINATION			= 'SMPP.IP.DESTINATION';
	SMPP_TCP_SOURCE				= 'SMPP.TCP.SOURCE';
	SMPP_TCP_DESTINATION			= 'SMPP.TCP.DESTINATION';
	SMPP_SYSTEM_ID				= 'SMPP.SYSTEM_ID';
	SMPP_PASSWORD				= 'SMPP.PASSWORD';
	SMPP_SERVICE_TYPE			= 'SMPP.SERVICE.TYPE';
	SMPP_ORIGINATOR_TON			= 'SMPP.ORIGINATOR.TON';
	SMPP_ORIGINATOR_NP			= 'SMPP.ORIGINATOR.NP';
	SMPP_ORIGINATOR_ADDRESS			= 'SMPP.ORIGINATOR.ADDRESS';
	SMPP_RECIPIENT_TON			= 'SMPP.RECIPIENT.TON';
	SMPP_RECIPIENT_NP			= 'SMPP.RECIPIENT.NP';
	SMPP_RECIPIENT_ADDRESS			= 'SMPP.RECIPIENT.ADDRESS';
	SMPP_ESM_MESSAGE_MODE			= 'SMPP.ESM.MESSAGE.MODE';
	SMPP_ESM_MESSAGE_TYPE			= 'SMPP.ESM.MESSAGE.TYPE';
	SMPP_ESM_GSM_FEATURES			= 'SMPP.ESM.GSM_FEATURES';
	SMPP_PROTOCOL_ID			= 'SMPP.PROTOCOL_ID';
	SMPP_PRIORITY_FLAG			= 'SMPP.PRIORITY.FLAG';
	SMPP_DELIVERY_TIME			= 'SMPP.DELIVERY_TIME';
	SMPP_VALIDITY_PERIOD			= 'SMPP.VALIDITY_PERIOD';
	// SMPP Registered delivery
	SMPP_RD_SMSC_RECEIPT			= 'SMPP.RD.SMSC_RECEIPT';
	SMPP_RD_SME_ACK				= 'SMPP.RD.SME_ACK';
	SMPP_RD_INTERMEDIATE_NOTIFICATION	= 'SMPP.RD.INTERMEDIATE_NOTIFICATION';

	SMPP_REPLACE_IF_PRESENT			= 'SMPP.REPLACE_IF_PRESENT';
	SMPP_DATA_CODING			= 'SMPP.DATA_CODING';
	SMPP_SM_DEFAULT_MSG_ID			= 'SMPP.SM_DEFAULT_MSG_ID';
	SMPP_SM_LENGTH				= 'SMPP.SM_LENGTH';
	SMPP_SM					= 'SMPP.SM';

	// SMPP ESM Message Mode
	SMPP_ESM_MM_DEFAULT			= 'SMPP.ESM.MM.DEFAULT';
	SMPP_ESM_MM_DATAGRAM			= 'SMPP.ESM.MM.DATAGRAM';
	SMPP_ESM_MM_FORWARD			= 'SMPP.ESM.MM.FORWARD';
	SMPP_ESM_MM_STORE_FORWARD		= 'SMPP.ESM.MM.STORE_FORWARD';

	// SMPP ESM Message Type
	SMPP_ESM_MT_DEFAULT			= 'SMPP.ESM.MT.DEFAULT';
	SMPP_ESM_MT_DELIVERY_ACK		= 'SMPP.ESM.MT.DELIVERY_ACK';
	SMPP_ESM_MT_MANUAL_USER_ACK		= 'SMPP.ESM.MT.MANUAL_USER_ACK';

	// SMPP ESM GSM Features
	SMPP_ESM_GF_NO				= 'SMPP.ESM.GF.NO';
	SMPP_ESM_GF_UDHI_INDICATOR		= 'SMPP.ESM.GF.UDHI_INDICATOR';
	SMPP_ESM_GF_SET_REPLY_PATH		= 'SMPP.ESM.GF.SET_REPLY_PATH';
	SMPP_ESM_GF_SET_BOTH			= 'SMPP.ESM.GF.SET_BOTH';


        // SMPP Type Of Number
        SMPP_TON_UNKNOWN                        = 'SMPP.TON.UNKNOWN';
        SMPP_TON_INTERNATIONAL                  = 'SMPP.TON.INTERNATIONAL';
        SMPP_TON_NATIONAL                       = 'SMPP.TON.NATIONAL';
        SMPP_TON_NETWORK_SPECIFIC               = 'SMPP.TON.NETWORK_SPECIFIC';
        SMPP_TON_SUBSCRIBER_NUMBER              = 'SMPP.TON.SUBSCRIBER_NUMBER';
        SMPP_TON_ALPHANUMERIC                   = 'SMPP.TON.ALPHANUMERIC';
        SMPP_TON_ABBREVIATED                    = 'SMPP.TON.ABBREVIATED';

	// SMPP Numbering Plan
        SMPP_NP_UNKNOWN                         = 'SMPP.NP.UNKNOWN';
        SMPP_NP_ISDN_TELEPHONE                  = 'SMPP.NP.ISDN_TELEPHONE';
        SMPP_NP_DATA_X121                       = 'SMPP.NP.DATA_X121';
        SMPP_NP_TELEX                           = 'SMPP.NP.TELEX';
        SMPP_NP_LAND_MOBILE                     = 'SMPP.NP.LAND_MOBILE';
        SMPP_NP_NATIONAL                        = 'SMPP.NP.NATIONAL';
        SMPP_NP_PRIVATE                         = 'SMPP.NP.PRIVATE';
        SMPP_NP_ERMES	                        = 'SMPP.NP.ERMES';
        SMPP_NP_INTERNET_IP                     = 'SMPP.NP.INTERNET_IP';
        SMPP_NP_WAP_CLIENT_ID                   = 'SMPP.NP.WAP_CLIENT_ID';
	
	// SMPP Registered delivery SMSC Delivery Receipt
	SMPP_RD_SMSCDR_NO			= 'SMPP.RD.SMSCDR.NO';
	SMPP_RD_SMSCDR_SUCCESS_FAILURE		= 'SMPP.RD.SMSCDR.SUCCESS_FAILURE';
	SMPP_RD_SMSCDR_FAILURE			= 'SMPP.RD.SMSCDR.FAILURE';

	// SMPP Registered delivery SME Orig Ack
	SMPP_RD_SMEOA_NO			= 'SMPP.RD.SMEOA.NO';
	SMPP_RD_SMEOA_ACK			= 'SMPP.RD.SMEOA.ACK';
	SMPP_RD_SMEOA_MANUAL_USER_ACK		= 'SMPP.RD.SMEOA.MANUAL_USER_ACK';
	SMPP_RD_SMEOA_BOTH			= 'SMPP.RD.SMEOA.BOTH';

	// SMPP Registered delivery Intermediate Notification
	SMPP_RD_IN_NO				= 'SMPP.RD.IN.NO';
	SMPP_RD_IN_YES				= 'SMPP.RD.IN.YES';


	// SMPP Data Coding
	SMPP_DC_DEFAULT				= 'SMPP.DC.DEFAULT';
	SMPP_DC_IA5_ASCII			= 'SMPP.DC.IA5_ASCII';
	SMPP_DC_8BIT_BINARY_1			= 'SMPP.DC.8BIT_BINARY_1';
	SMPP_DC_ISO_8859_1			= 'SMPP.DC.ISO_8859_1';
	SMPP_DC_8BIT_BINARY_2			= 'SMPP.DC.8BIT_BINARY_2';
	SMPP_DC_JIS				= 'SMPP.DC.JIS';
	SMPP_DC_ISO_8859_5			= 'SMPP.DC.ISO_8859_5';
	SMPP_DC_ISO_8859_8			= 'SMPP.DC.ISO_8859_8';
	SMPP_DC_UCS2				= 'SMPP.DC.UCS2';
	SMPP_DC_PICTOGRAM			= 'SMPP.DC.PICTOGRAM';
	SMPP_DC_ISO_2011_JP			= 'SMPP.DC.ISO_2011_JP';
	SMPP_DC_EXTENDED_KANJI			= 'SMPP.DC.EXTENDED_KANJI';
	SMPP_DC_KS_C_5601			= 'SMPP.DC.KS_C_5601';


	// eval items
	SCCP_GT_CALLED_ADDRESS			= 'SCCP.GT_CALLED.ADDRESS';
	SCCP_GT_CALLING_ADDRESS			= 'SCCP.GT_CALLING.ADDRESS';
	SCCP_GT_CALLED_TT			= 'SCCP.GT_CALLED.TT';
	SCCP_GT_CALLING_TT			= 'SCCP.GT_CALLING.TT';
	SCCP_GT_CALLED_NAI			= 'SCCP.GT_CALLED.NAI';
	SCCP_GT_CALLING_NAI			= 'SCCP.GT_CALLING.NAI';
	SCCP_GT_CALLED_NP			= 'SCCP.GT_CALLED.NP';
	SCCP_GT_CALLING_NP			= 'SCCP.GT_CALLING.NP';
	SCCP_GT_CALLED_GTI			= 'SCCP.GT_CALLED.GTI';
	SCCP_GT_CALLING_GTI			= 'SCCP.GT_CALLING.GTI';
	MAP_SCOA				= 'MAP.SCOA'; 
	MAP_SCDA				= 'MAP.SCDA';
	MAP_IMSI				= 'MAP.IMSI';
	MAP_MSISDN				= 'MAP.MSISDN';
	M3UA_DPC				= 'M3UA.DPC';
	M3UA_OPC				= 'M3UA.OPC';
	SMS_TPDU_ORIGINATING			= 'SMS_TPDU.ORIGINATING';
	SMS_TPDU_ORIGINATING_ENC		= 'SMS_TPDU.ORIGINATING.ENC';
	SMS_TPDU_DESTINATION			= 'SMS_TPDU.DESTINATION';
	SMS_TPDU_DESTINATION_ENC		= 'SMS_TPDU.DESTINATION.ENC';
	SMS_TPDU_UD				= 'SMS_TPDU.UD';
	DICT_SMS_TPDU_UD			= 'DICT.SMS';

	// HLR
	HLR_IMSI				= 'HLR.IMSI';
	HLR_MSISDN				= 'HLR.MSISDN';
	HLR_NNN					= 'HLR.NNN';
	HLR_ANNN				= 'HLR.ANNN';
	HLR_SCA					= 'HLR.SCA';

	// HLR RESULT
        HLR_RESULT_IMSI                         = 'HLR.RESULT.IMSI';
        HLR_RESULT_NNN     	                = 'HLR.RESULT.NNN';
        HLR_RESULT_ANNN                         = 'HLR.RESULT.ANNN';
	
	// LD known spam
	SPAM_SMS_TPDU_UD			= 'SPAM.SMS';

	// LD repetitions
	RP_SMS_TPDU_UD				= 'RP.SMS';
	
	// Quarantine
	QUARANTINE_SMS_TPDU_UD			= 'QUARANTINE.SMS';
	
	// MD5
	MD5_SMS_TPDU_UD				= 'MD5.SMS';
	
	SMS_TPDU_DCS				= 'SMS_TPDU.DCS';
	SMS_MSG_TYPE				= 'SMS.MSG_TYPE';
	
	// Type Of Number
	TON_UNKNOWN				= 'TON.UNKNOWN';
	TON_INTERNATIONAL			= 'TON.INTERNATIONAL';
	TON_NATIONAL				= 'TON.NATIONAL';
	TON_NETWORK_SPECIFIC			= 'TON.NETWORK_SPECIFIC';
	TON_SUBSCRIBER_NUMBER			= 'TON.SUBSCRIBER_NUMBER';
	TON_ALPHANUMERIC			= 'TON.ALPHANUMERIC';
	TON_ABBREVIATED				= 'TON.ABBREVIATED';

	// SCCP NP
	NP_UNKNOWN				= 'NP.UNKNOWN';
	NP_ISDN_TELEPHONE			= 'NP.ISDN_TELEPHONE';
	NP_GENERIC				= 'NP.GENERIC';
	NP_DATA_X121				= 'NP.DATA_X121';
	NP_TELEX				= 'NP.TELEX';
	NP_MARITIME				= 'NP.MARITIME';
	NP_LAND_MOBILE				= 'NP.LAND_MOBILE';
	NP_ISDN_MOBILE				= 'NP.ISDN_MOBILE';
	NP_PRIVATE				= 'NP.PRIVATE';

	// SCCP NAI
	NAI_UNKNOWN				= 'NAI.UNKNOWN';
	NAI_SUBSCRIBER_NUMBER			= 'NAI.SUBSCRIBER_NUMBER';
	NAI_RESERVED_FOR_NATIONAL_USE		= 'NAI.RESERVED_FOR_NATIONAL_USE';
	NAI_NATIONAL_SIGNIFICANT_NUMBER		= 'NAI.NAI_NATIONAL_SIGNIFICANT_NUMBER';
	NAI_INTERNATIONAL			= 'NAI.NAI_INTERNATIONAL';	
	
	// SCCP GT GTI
	GTI_NONE				= 'GTI.NONE';
	GTI_NAI					= 'GTI.NAI_ONLY';
	GTI_TT					= 'GTI.TT_ONLY';
	GTI_TTNPE				= 'GTI.TTNPE';
	GTI_TTNPENOA				= 'GTI.TTNPENOA';

	// DCS
	DCS_DEFAULT				= 'DCS.DEFAULT';
	DCS_8BIT				= 'DCS.8BIT';
	DCS_UCS2				= 'DCS.UCS2';
	
	// MSG Type
	MSG_TYPE_SINGLE				= 'MSG_TYPE.SINGLE';
	MSG_TYPE_CONCATENATED			= 'MSG_TYPE.CONCATENATED';


	// Modifier methods
	SPAM_UPDATE_LST				= 'SPAM.UPDATE_LST';	
	SPAM_REMOVE_LST				= 'SPAM.REMOVE';
	QUARANTINE_UPDATE_LST			= 'QUARANTINE.UPDATE_LST';
	QUARANTINE_REMOVE_LST			= 'QUARANTINE.REMOVE';
	MD5_UPDATE_LST				= 'MD5.UPDATE_LST';
	MD5_REMOVE_LST				= 'MD5.REMOVE';
	HLR_REQUEST				= 'HLR.REQUEST';
	NO_DR					= 'NO.DR';
	CONVERT_SS7				= 'CONVERT.SS7';
	CONVERT_SMPP				= 'CONVERT.SMPP';


	// rule methods
	FLOOD					= 'FLOOD';
	FLOOD_MAX				= 'FLOOD.MAX';	
	FLOOD_GLOBAL				= 'FLOOD.GLOBAL';
	FLOOD_GLOBAL_MAX			= 'FLOOD.GLOBAL.MAX';
	FLOOD_ALL_MAX				= 'FLOOD.ALL.MAX';
	FLOOD_HOUR				= 'HOUR';
	FLOOD_MINUTE				= 'MINUTE';
	FLOOD_DAY				= 'DAY';
	FLOOD_ALL				= 'ALL';
	LIST					= 'LIST';
	

	// other tokens
	RULE					= 'RULE';
	IN					= 'IN';
	NOT_IN					= 'NIN';
	CONT					= 'CONTINUE';
	CONT_Q					= 'CONTINUE_QUARANTINE';
	ALW					= 'ALLOW';
	ALW_Q					= 'ALLOW_QUARANTINE';
	ALWU					= 'ALLOW_UNCONDITIONAL';
	ALWU_Q					= 'ALLOW_UNCONDITIONAL_QUARANTINE';
	DNY					= 'DENY';
	DNY_Q					= 'DENY_QUARANTINE';
	L_PAREN					= '(';
	R_PAREN					= ')';
	R_SQ_B					= ']';
	L_SQ_B					= '[';
	L_CR_B					= '{';
	R_CR_B					= '}';
	F_MO					= 'MO';
	F_SMPP_MO				= 'SMPP_MO';
	F_MT					= 'MT';
	F_SMPP_MT				= 'SMPP_MT';
	F_HLR					= 'HLR';
	F_M3UA					= 'M3UA';
	ON					= 'ON';
	OFF					= 'OFF';
	ANNT					= '@';
	EQUAL					= '==';
	ASSIGN					= '=';
	OR					= '||';
	NEQUAL					= '!=';
	COLON					= ':';
	STMTSEP					= ';';
	PERCENT					= '%';
	HEX_P					= '0x';
	LESS_THAN				= '<';
	GT					= '>';
	LTE					= '<=';
	GTE					= '>=';
	PLUS					= '+';
	MINUS					= '-';
	AND					= '&&';
	OR					= '||';
	MODIFY					= 'MODIFY';
	ASSIGN					= '=';
	SQUOTE					= '\'';
	DQUOTE					= '"';
	GOTO					= 'GOTO';
	REGEX_BLOCK				= '/';
	ASTERISK				= '*';
	COMMA					= ',';
	// AST
	FILTER_NODE;
	RULE_EVAL;
	RULE_STATUS;
	RULE_EVAL_ATOM;
	RULE_REGEX;
	RULE_REGEX_EXPR;
	RULE_EVAL_TRUE;
	RULE_EVAL_FALSE;
	RULE_EVAL_POINTS;
	RULE_DEF;
	DUMMY_RULE_DEF;
	RULE_LABEL;
	MODIFIER;
	MODIFIER_STATUS;
	MODIFIER_METHOD;
	MODIFIER_LABEL;
	M3UA_CONNECTION;
	CONNECTION_LABEL;
	LOCAL_IP;
	LOCAL_PORT;
	REMOTE_IP;
	REMOTE_PORT;
	CONN_DPC;
	CONN_OPC;
	CONN_N_APP;
	CONN_RC;
	CONN_SC;
	HLR_MSISDN;
	HLR_SCA;
}

input
  : (filter)* EOF!
  ;

eval_nai
  : SCCP_GT_CALLED_NAI
  | SCCP_GT_CALLING_NAI
  ;

smpp_eval_np
  : SMPP_ORIGINATOR_NP
  | SMPP_RECIPIENT_NP
  ;


eval_np
  : SCCP_GT_CALLED_NP
  | SCCP_GT_CALLING_NP
  ;

eval_gti
  : SCCP_GT_CALLED_GTI
  | SCCP_GT_CALLING_GTI
  ;

eval_dcs
  : SMS_TPDU_DCS
  ;

smpp_eval_dcs
  : SMPP_DATA_CODING
  ;

smpp_eval_esm_mm
  : SMPP_ESM_MESSAGE_MODE
  ;

smpp_eval_esm_mt
  : SMPP_ESM_MESSAGE_TYPE
  ;

smpp_eval_esm_gf
  : SMPP_ESM_GSM_FEATURES
  ;

smpp_eval_rd_smscdr
  : SMPP_RD_SMSC_RECEIPT
  ;

smpp_eval_rd_smeoa
  : SMPP_RD_SME_ACK
  ;

smpp_eval_rd_in
  : SMPP_RD_INTERMEDIATE_NOTIFICATION
  ;



eval_string
  : SCCP_GT_CALLED_ADDRESS
  | SCCP_GT_CALLING_ADDRESS
  | MAP_SCOA
  | MAP_SCDA
  | MAP_IMSI
  | MAP_MSISDN
  | SMS_TPDU_ORIGINATING
  | SMS_TPDU_DESTINATION
  | SMS_TPDU_UD
  // HLR
  | HLR_IMSI
  | HLR_MSISDN
  | HLR_NNN
  | HLR_ANNN
  | HLR_SCA
  // HLR RESULT
  | HLR_RESULT_IMSI
  | HLR_RESULT_NNN
  | HLR_RESULT_ANNN
  // SMPP
  | SMPP_IP_SOURCE
  | SMPP_IP_DESTINATION
  | SMPP_SYSTEM_ID
  | SMPP_PASSWORD
  | SMPP_SERVICE_TYPE
  | SMPP_ORIGINATOR_ADDRESS
  | SMPP_RECIPIENT_ADDRESS
  | SMPP_SM
  ;

eval_number
  : M3UA_DPC
  | M3UA_OPC
  | DICT_SMS_TPDU_UD
  | SPAM_SMS_TPDU_UD
  | RP_SMS_TPDU_UD
  | QUARANTINE_SMS_TPDU_UD
  | MD5_SMS_TPDU_UD
  | SCCP_GT_CALLED_TT
  | SCCP_GT_CALLING_TT
  // SMPP
  | SMPP_TCP_SOURCE
  | SMPP_TCP_DESTINATION
  | SMPP_DELIVERY_TIME
  | SMPP_VALIDITY_PERIOD
  | SMPP_SM_DEFAULT_MSG_ID
  | SMPP_SM_LENGTH
  | SMPP_PROTOCOL_ID
  ;

eval_ton 
  : SMS_TPDU_ORIGINATING_ENC
  | SMS_TPDU_DESTINATION_ENC
  ;

smpp_eval_ton
  : SMPP_ORIGINATOR_TON
  | SMPP_RECIPIENT_TON
  ;


eval_msg_type
  : SMS_MSG_TYPE
  ;

evalsimple
  : L_PAREN WS* w=eval_string WS* a=comparison WS* (b=SCCP_GT_CALLED_WL|b=SCCP_GT_CALLING_WL|b=MAP_SCOA_WL|b=MAP_SCDA_WL) WS* R_PAREN -> ^(RULE_EVAL_ATOM $w $a $b)
  | L_PAREN WS* w=eval_string WS* a=comparison WS* bstr=STRINGLITERAL WS* R_PAREN -> ^(RULE_EVAL_ATOM $w $a $bstr)
  | L_PAREN WS* w1=eval_dcs WS* a=comparison WS* br1=dcs WS* R_PAREN -> ^(RULE_EVAL_ATOM $w1 $a $br1)
  | L_PAREN WS* w2=eval_number WS* a=comparison WS* br2=DIGITS PERCENT* WS* R_PAREN -> ^(RULE_EVAL_ATOM $w2 $a $br2)
  | L_PAREN WS* w3=eval_ton WS* a=comparison WS* br3=typeofnum WS* R_PAREN -> ^(RULE_EVAL_ATOM $w3 $a $br3)
  | L_PAREN WS* w4=eval_msg_type WS* a=comparison WS* br4=msgtype WS* R_PAREN -> ^(RULE_EVAL_ATOM $w4 $a $br4) 
  | L_PAREN WS* w5=eval_string WS* a=comparison WS* br5=eval_string WS* R_PAREN -> ^(RULE_EVAL_ATOM $w5 $a $br5) 
  | L_PAREN WS* w6=eval_number WS* a=comparison WS* br6=eval_number WS* R_PAREN -> ^(RULE_EVAL_ATOM $w6 $a $br6) 
  // SCCP NAI
  | L_PAREN WS* w7=eval_nai WS* a=comparison WS* br7=nai WS* R_PAREN -> ^(RULE_EVAL_ATOM $w7 $a $br7)
  // SCCP NP
  | L_PAREN WS* w8=eval_np WS* a=comparison WS* br8=np WS* R_PAREN -> ^(RULE_EVAL_ATOM $w8 $a $br8)
  // SCCP GTI
  | L_PAREN WS* w9=eval_gti WS* a=comparison WS* br9=gti WS* R_PAREN -> ^(RULE_EVAL_ATOM $w9 $a $br9)
  // SMPP NP
  | L_PAREN WS* w10=smpp_eval_np WS* a=comparison WS* br10=smpp_np WS* R_PAREN -> ^(RULE_EVAL_ATOM $w10 $a $br10)
  // SMPP TON
  | L_PAREN WS* w11=smpp_eval_ton WS* a=comparison WS* br11=smpp_typeofnum WS* R_PAREN -> ^(RULE_EVAL_ATOM $w11 $a $br11)
  // SMPP ESM MM
  | L_PAREN WS* w12=smpp_eval_esm_mm WS* a=comparison WS* br12=smpp_esm_mm WS* R_PAREN -> ^(RULE_EVAL_ATOM $w12 $a $br12)
  // SMPP ESM MT
  | L_PAREN WS* w13=smpp_eval_esm_mt WS* a=comparison WS* br13=smpp_esm_mt WS* R_PAREN -> ^(RULE_EVAL_ATOM $w13 $a $br13)
  // SMPP ESM GT
  | L_PAREN WS* w14=smpp_eval_esm_gf WS* a=comparison WS* br14=smpp_esm_gf WS* R_PAREN -> ^(RULE_EVAL_ATOM $w14 $a $br14)
  // SMPP RD SMSC DR
  | L_PAREN WS* w15=smpp_eval_rd_smscdr WS* a=comparison WS* br15=smpp_rd_smscdr WS* R_PAREN -> ^(RULE_EVAL_ATOM $w15 $a $br15)
  // SMPP RD SME OA
  | L_PAREN WS* w16=smpp_eval_rd_smeoa WS* a=comparison WS* br16=smpp_rd_smeoa WS* R_PAREN -> ^(RULE_EVAL_ATOM $w16 $a $br16)
  // SMPP RD IN
  | L_PAREN WS* w17=smpp_eval_rd_in WS* a=comparison WS* br17=smpp_rd_in WS* R_PAREN -> ^(RULE_EVAL_ATOM $w17 $a $br17)

  // Special RULE methods
  // flood methods
  | L_PAREN WS* fvar=floodmethod WS* a=comparison WS* fvar2=floodmethod WS* R_PAREN -> ^(RULE_EVAL_ATOM $fvar $a $fvar2)
  | L_PAREN WS* fvar=floodmethod WS* a=comparison WS* fdigs=DIGITS WS* R_PAREN -> ^(RULE_EVAL_ATOM $fvar $a $fdigs)
  // list methods
  | L_PAREN WS* w=eval_string WS* a=comparison WS* lvar=listmethod WS* R_PAREN -> ^(RULE_EVAL_ATOM $w $a $lvar)
  ;

listmethod
  : s=LIST WS* L_PAREN WS* sl=STRINGLITERAL WS* R_PAREN -> ^($s $sl)
  ;
 
floodmethod
  : s=FLOOD WS* L_PAREN WS* e=eval_string WS* COMMA WS* (fi=FLOOD_MINUTE | fi=FLOOD_HOUR | fi=FLOOD_DAY) WS* R_PAREN -> ^($s $e $fi)
  | s=FLOOD_GLOBAL WS* L_PAREN WS* (fi=FLOOD_MINUTE | fi=FLOOD_HOUR | fi=FLOOD_DAY) WS* R_PAREN -> ^($s $fi)
  | s=FLOOD_MAX  WS* L_PAREN WS* e=eval_string WS* COMMA WS* (fi=FLOOD_MINUTE | fi=FLOOD_HOUR | fi=FLOOD_DAY) WS* R_PAREN -> ^($s $e $fi)
  | s=FLOOD_GLOBAL_MAX WS* L_PAREN WS* (fi=FLOOD_MINUTE | fi=FLOOD_HOUR | fi=FLOOD_DAY) WS* R_PAREN -> ^($s $fi)
  | s=FLOOD_ALL_MAX WS* L_PAREN WS* (fi=FLOOD_MINUTE | fi=FLOOD_HOUR | fi=FLOOD_DAY) WS* R_PAREN -> ^($s $fi)
  ;




regexdef returns [pANTLR3_STRING regexdef_res]
  : { pANTLR3_STRING_FACTORY strf = $text->factory; $regexdef_res = strf->newRaw(strf); }(WORD{ $regexdef_res->append8($regexdef_res, (char*)$WORD.text->chars); }|DIGITS{ $regexdef_res->append8($regexdef_res, (char*)$DIGITS.text->chars); }|'^'{ $regexdef_res->append8($regexdef_res, "^");}|'$'{  $regexdef_res->append8($regexdef_res, "$"); }|'['{  $regexdef_res->append8($regexdef_res, "["); }|']'{  $regexdef_res->append8($regexdef_res, "]"); }|'('{  $regexdef_res->append8($regexdef_res, "("); }|')'{  $regexdef_res->append8($regexdef_res, ")"); }|'.'{  $regexdef_res->append8($regexdef_res, "."); }|'*'{  $regexdef_res->append8($regexdef_res, "*"); }|'?'{  $regexdef_res->append8($regexdef_res, "?"); }|'+'{  $regexdef_res->append8($regexdef_res, "+"); }|'\\'{  $regexdef_res->append8($regexdef_res, "\\"); })*
  ;
  
regex
  // string regex -> string value
  : L_PAREN WS* REGEX_BLOCK r=regexdef REGEX_BLOCK b2=eval_string WS* c2=comparison WS* bstr=STRINGLITERAL WS* R_PAREN -> ^(RULE_EVAL_ATOM^(RULE_REGEX^(RULE_REGEX_EXPR[$r.regexdef_res->chars]) $b2) $c2 $bstr)
  // string regex -> string
  | L_PAREN WS* REGEX_BLOCK r=regexdef REGEX_BLOCK b2=eval_string WS* c2=comparison WS* d3=eval_string WS* R_PAREN -> ^(RULE_EVAL_ATOM^(RULE_REGEX^(RULE_REGEX_EXPR[$r.regexdef_res->chars]) $b2) $c2 $d3)
  // string regex -> string regex
  | L_PAREN WS* REGEX_BLOCK r=regexdef REGEX_BLOCK b2=eval_string WS* c2=comparison WS* REGEX_BLOCK r2=regexdef REGEX_BLOCK bb2=eval_string WS* R_PAREN -> ^(RULE_EVAL_ATOM^(RULE_REGEX^(RULE_REGEX_EXPR[$r.regexdef_res->chars]) $b2) $c2 ^(RULE_REGEX^(RULE_REGEX_EXPR[$r2.regexdef_res->chars]) $bb2))
  // number regex -> number value
  | L_PAREN WS* REGEX_BLOCK r=regexdef REGEX_BLOCK bn2=eval_number WS* c2=comparison WS* d2=DIGITS WS* R_PAREN -> ^(RULE_EVAL_ATOM^(RULE_REGEX^(RULE_REGEX_EXPR[$r.regexdef_res->chars]) $bn2) $c2 $d2)
  // number regex -> number
  | L_PAREN WS* REGEX_BLOCK r=regexdef REGEX_BLOCK bn2=eval_number WS* c2=comparison WS* bn3=eval_number WS* R_PAREN -> ^(RULE_EVAL_ATOM^(RULE_REGEX^(RULE_REGEX_EXPR[$r.regexdef_res->chars]) $bn2) $c2 $bn3)
  // number regex -> number regex
  | L_PAREN WS* REGEX_BLOCK r=regexdef REGEX_BLOCK bn2=eval_number WS* c2=comparison WS* REGEX_BLOCK r2=regexdef REGEX_BLOCK bn3=eval_number WS* R_PAREN -> ^(RULE_EVAL_ATOM^(RULE_REGEX^(RULE_REGEX_EXPR[$r.regexdef_res->chars]) $bn2) $c2 ^(RULE_REGEX^(RULE_REGEX_EXPR[$r2.regexdef_res->chars]) $bn3))
  // string regex -> number regex
  | L_PAREN WS* REGEX_BLOCK r=regexdef REGEX_BLOCK b2=eval_string WS* c2=comparison WS* REGEX_BLOCK r2=regexdef REGEX_BLOCK bn3=eval_number WS* R_PAREN -> ^(RULE_EVAL_ATOM^(RULE_REGEX^(RULE_REGEX_EXPR[$r.regexdef_res->chars]) $b2) $c2 ^(RULE_REGEX^(RULE_REGEX_EXPR[$r2.regexdef_res->chars]) $bn3))
  // number regex -> string regex
  | L_PAREN WS* REGEX_BLOCK r=regexdef REGEX_BLOCK bn2=eval_number WS* c2=comparison WS* REGEX_BLOCK r2=regexdef REGEX_BLOCK b2=eval_string WS* R_PAREN -> ^(RULE_EVAL_ATOM^(RULE_REGEX^(RULE_REGEX_EXPR[$r.regexdef_res->chars]) $bn2) $c2 ^(RULE_REGEX^(RULE_REGEX_EXPR[$r2.regexdef_res->chars]) $b2))
  // string regex -> number
  | L_PAREN WS* REGEX_BLOCK r=regexdef REGEX_BLOCK b2=eval_string WS* c2=comparison WS* d2=DIGITS WS* R_PAREN -> ^(RULE_EVAL_ATOM^(RULE_REGEX^(RULE_REGEX_EXPR[$r.regexdef_res->chars]) $b2) $c2 $d2)
  // number regex -> string value
  | L_PAREN WS* REGEX_BLOCK r=regexdef REGEX_BLOCK bn2=eval_number WS* c2=comparison WS* bstr=STRINGLITERAL WS* R_PAREN -> ^(RULE_EVAL_ATOM^(RULE_REGEX^(RULE_REGEX_EXPR[$r.regexdef_res->chars]) $bn2) $c2 $bstr)
  // number regex -> string
  | L_PAREN WS* REGEX_BLOCK r=regexdef REGEX_BLOCK bn2=eval_number WS* c2=comparison WS* d3=eval_string WS* R_PAREN -> ^(RULE_EVAL_ATOM^(RULE_REGEX^(RULE_REGEX_EXPR[$r.regexdef_res->chars]) $bn2) $c2 $d3)
  ;


smpp_esm_mm
  : SMPP_ESM_MM_DEFAULT
  | SMPP_ESM_MM_DATAGRAM
  | SMPP_ESM_MM_FORWARD
  | SMPP_ESM_MM_STORE_FORWARD
  ;

smpp_esm_mt
  : SMPP_ESM_MT_DEFAULT
  | SMPP_ESM_MT_DELIVERY_ACK
  | SMPP_ESM_MT_MANUAL_USER_ACK
  ;

smpp_esm_gf
  : SMPP_ESM_GF_NO
  | SMPP_ESM_GF_UDHI_INDICATOR
  | SMPP_ESM_GF_SET_REPLY_PATH
  | SMPP_ESM_GF_SET_BOTH
  ;

smpp_rd_smscdr
  : SMPP_RD_SMSCDR_NO
  | SMPP_RD_SMSCDR_SUCCESS_FAILURE
  | SMPP_RD_SMSCDR_FAILURE
  ;

smpp_rd_smeoa
  : SMPP_RD_SMEOA_NO
  | SMPP_RD_SMEOA_ACK
  | SMPP_RD_SMEOA_MANUAL_USER_ACK
  | SMPP_RD_SMEOA_BOTH
  ;

smpp_rd_in
  : SMPP_RD_IN_NO
  | SMPP_RD_IN_YES
  ;


nai
  : NAI_UNKNOWN
  | NAI_SUBSCRIBER_NUMBER
  | NAI_RESERVED_FOR_NATIONAL_USE
  | NAI_NATIONAL_SIGNIFICANT_NUMBER
  | NAI_INTERNATIONAL
  ;

np
  : NP_UNKNOWN
  | NP_ISDN_TELEPHONE
  | NP_GENERIC
  | NP_DATA_X121
  | NP_TELEX
  | NP_MARITIME
  | NP_LAND_MOBILE
  | NP_ISDN_MOBILE
  | NP_PRIVATE
  ;

smpp_np
  : SMPP_NP_UNKNOWN
  | SMPP_NP_ISDN_TELEPHONE
  | SMPP_NP_DATA_X121
  | SMPP_NP_TELEX
  | SMPP_NP_LAND_MOBILE
  | SMPP_NP_NATIONAL
  | SMPP_NP_PRIVATE
  | SMPP_NP_ERMES
  | SMPP_NP_INTERNET_IP
  | SMPP_NP_WAP_CLIENT_ID
  ;


gti
  : GTI_NONE
  | GTI_NAI
  | GTI_TT
  | GTI_TTNPE
  | GTI_TTNPENOA
  ;

smpp_dcs
  : SMPP_DC_DEFAULT
  | SMPP_DC_IA5_ASCII
  | SMPP_DC_8BIT_BINARY_1
  | SMPP_DC_ISO_8859_1
  | SMPP_DC_8BIT_BINARY_2
  | SMPP_DC_JIS
  | SMPP_DC_ISO_8859_5
  | SMPP_DC_ISO_8859_8
  | SMPP_DC_UCS2
  | SMPP_DC_PICTOGRAM
  | SMPP_DC_ISO_2011_JP
  | SMPP_DC_EXTENDED_KANJI
  | SMPP_DC_KS_C_5601
  ;

dcs
  : DCS_DEFAULT
  | DCS_8BIT
  | DCS_UCS2
  ;
 

smpp_typeofnum
  : SMPP_TON_UNKNOWN
  | SMPP_TON_INTERNATIONAL
  | SMPP_TON_NATIONAL
  | SMPP_TON_NETWORK_SPECIFIC
  | SMPP_TON_SUBSCRIBER_NUMBER
  | SMPP_TON_ALPHANUMERIC
  | SMPP_TON_ABBREVIATED
  ;
 
typeofnum
  : TON_UNKNOWN
  | TON_INTERNATIONAL
  | TON_NATIONAL
  | TON_NETWORK_SPECIFIC
  | TON_SUBSCRIBER_NUMBER
  | TON_ALPHANUMERIC
  | TON_ABBREVIATED
  ;

msgtype
  : MSG_TYPE_SINGLE
  | MSG_TYPE_CONCATENATED
  ;

evalobj
  : eval_dcs
  | eval_string
  | eval_number
  | eval_ton
  | eval_msg_type
  | eval_nai
  | eval_np
  | eval_gti
  ;

eval
  : evalsimple
  | regex
  ;

curlyblock
  : L_CR_B! (curlyblock | WS | rule | rulebody | modify | modifybody | m3ua)* R_CR_B!
  ;

// m3ua
m3ua
  : COLON WS* L_PAREN WS* lbl=WORD def=ASTERISK* WS* COLON WS* lip=IP WS* COLON WS* lp=DIGITS WS* COLON WS* rip=IP WS* COLON WS* rp=DIGITS WS* COLON WS* dpc=DIGITS WS* COLON WS* opc=DIGITS WS* COLON WS* napp=DIGITS WS* COLON WS* rc=DIGITS WS* COLON WS* sc=DIGITS WS* R_PAREN WS* STMTSEP -> ^(M3UA_CONNECTION^(CONNECTION_LABEL $lbl $def?) ^(LOCAL_IP $lip) ^(LOCAL_PORT $lp) ^(REMOTE_IP $rip) ^(REMOTE_PORT $rp) ^(CONN_DPC $dpc) ^(CONN_OPC $opc) ^(CONN_N_APP $napp) ^(CONN_RC $rc) ^(CONN_SC $sc))
  ;

IP
  : DIGITS '.' DIGITS '.' DIGITS '.' DIGITS
  ;


modifier_method
  : SPAM_UPDATE_LST
  | SPAM_REMOVE_LST
  | QUARANTINE_UPDATE_LST
  | QUARANTINE_REMOVE_LST
  | MD5_UPDATE_LST
  | MD5_REMOVE_LST 
  | NO_DR
  | CONVERT_SS7
  | CONVERT_SMPP
  // special like hlr request
  | r=HLR_REQUEST WS* L_PAREN WS* msisdn=STRINGLITERAL WS* COMMA WS* sca=STRINGLITERAL WS* R_PAREN -> ^($r ^(HLR_MSISDN $msisdn) ^(HLR_SCA $sca))
  | r=HLR_REQUEST WS* L_PAREN WS* msisdn1=eval_string WS* COMMA WS* sca1=eval_string WS* R_PAREN -> ^($r ^(HLR_MSISDN $msisdn1) ^(HLR_SCA $sca1))
  | r=HLR_REQUEST WS* L_PAREN WS* msisdn2=eval_string WS* COMMA WS* sca2=STRINGLITERAL WS* R_PAREN -> ^($r ^(HLR_MSISDN $msisdn2) ^(HLR_SCA $sca2))
  | r=HLR_REQUEST WS* L_PAREN WS* msisdn3=STRINGLITERAL WS* COMMA WS* sca3=eval_string WS* R_PAREN -> ^($r ^(HLR_MSISDN $msisdn3) ^(HLR_SCA $sca3))
  ;

modify
  : L_SQ_B ANNT (ra=ON | ra=OFF) R_SQ_B COLON MODIFY WS* curlyblock  -> ^(MODIFIER^(MODIFIER_STATUS $ra) curlyblock)
  | lbl=WORD COLON L_SQ_B ANNT (ra=ON | ra=OFF) R_SQ_B COLON MODIFY WS* curlyblock  -> ^(MODIFIER^(MODIFIER_STATUS $ra) curlyblock ^(MODIFIER_LABEL $lbl))
  ;

modifybody
  : COLON WS* w=evalobj WS* ASSIGN WS* b=STRINGLITERAL WS* STMTSEP -> ^($w $b)
  | COLON WS* w=evalobj WS* ASSIGN WS* w2=evalobj WS* STMTSEP -> ^($w $w2)
  | COLON WS* wm=modifier_method WS* STMTSEP -> ^(MODIFIER_METHOD $wm)
  ;

ruleeval
  : COLON! WS* eval WS* STMTSEP! 
  ;

rulealw
  : PLUS WS* action WS* STMTSEP
  -> ^(RULE_EVAL_TRUE action)
  ;

ruledny
  : MINUS WS* action WS* STMTSEP
  -> ^(RULE_EVAL_FALSE action)
  ;

// normal rule body and action only body
rulebody
  : ruleeval WS* rulealw WS* ruledny
  | COLON! WS* L_PAREN! WS* action WS* R_PAREN! WS* STMTSEP!
  ;

rule
  // normal rule without label and normal rule with label
  : L_SQ_B ANNT (ra=ON | ra=OFF) R_SQ_B COLON RULE L_SQ_B d=DIGITS* R_SQ_B WS* curlyblock -> ^(RULE_DEF^(RULE_EVAL_POINTS $d) ^(RULE_STATUS $ra) curlyblock)
  | lbl=WORD COLON L_SQ_B ANNT (ra=ON | ra=OFF) R_SQ_B COLON RULE L_SQ_B d=DIGITS* R_SQ_B WS* curlyblock -> ^(RULE_DEF^(RULE_EVAL_POINTS $d) ^(RULE_STATUS $ra) curlyblock ^(RULE_LABEL $lbl))
  // dummy rule without label and dummy rule with label
  | L_SQ_B ANNT (ra=ON | ra=OFF) R_SQ_B COLON RULE WS* curlyblock -> ^(DUMMY_RULE_DEF^(RULE_STATUS $ra) curlyblock)
  | lbl=WORD COLON L_SQ_B ANNT (ra=ON | ra=OFF) R_SQ_B COLON RULE WS* curlyblock -> ^(DUMMY_RULE_DEF^(RULE_STATUS $ra) curlyblock ^(RULE_LABEL $lbl))
  ;

filter
  : (ftype=F_MO | ftype=F_MT | ftype=F_SMPP_MO | ftype=F_SMPP_MT | ftype=F_HLR | ftype=F_M3UA) WS* curlyblock WS* -> ^(FILTER_NODE^($ftype curlyblock))
  ;

ML_COMMENT
  : '/*' (options {greedy=false;} : .)* '*/' {$channel=HIDDEN;}
  ;

SL_COMMENT
  : '//' (options {greedy=false;} : .)* '\n' {$channel=HIDDEN;}
  ;

DIGITS
  : '0'..'9'+
  ;

DECIMAL
  : DIGITS '.' DIGITS
  ;

comparison 
  : EQUAL
  | NEQUAL
  | LESS_THAN
  | GT
  | LTE
  | GTE
  | IN
  | NOT_IN
  ;

action
  : CONT
  | CONT_Q
  | ALW
  | ALW (COLON! WORD)+
  | ALW_Q
  | ALW_Q (COLON! WORD)+
  | ALWU
  | ALWU (COLON! WORD)+
  | ALWU_Q
  | ALWU_Q (COLON! WORD)+
  | DNY
  | DNY (COLON! WORD)+
  | DNY_Q
  | DNY_Q (COLON! WORD)+
  | g=GOTO WS* d=WORD -> ^($g $d)
  ;


//LETTERS
//  : ('a'..'z'|'A'..'Z')+
//  ;

WORD
  : ('a'..'z'|'A'..'Z'|'0'..'9'|'.'|'_')*
  ;


WS
  : (' ' | '\t' | '\r' | '\n'){$channel=HIDDEN;}
  ;


STRINGLITERAL
    : DQUOTE
        (   ESCAPESEQUENCE
        |   ~( '\\' | DQUOTE | '\r' | '\n' )
        )*
        DQUOTE
	// remove first and last double quote in output
	{ 
		pANTLR3_STRING tmp_str = GETTEXT();
		SETTEXT(tmp_str->subString(tmp_str, 1, tmp_str->len-1));
	}
	//{ setText(getText().substring(1, getText().length() - 1)); }
    ;


fragment
ESCAPESEQUENCE
    :   '\\' (
                 'b'
             |   't'
             |   'n'
             |   'f'
             |   'r'
             |   '\"'
             |   '\''
             |   '\\'
             |
                 ('0'..'3') ('0'..'7') ('0'..'7')
             |
                 ('0'..'7') ('0'..'7')
             |
                 ('0'..'7')
             )
    ;

