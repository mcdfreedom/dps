/*
Navicat MySQL Data Transfer

Source Server         : NS4-test
Source Server Version : 50721
Source Host           : 192.168.1.48:3306
Source Database       : dcd

Target Server Type    : MYSQL
Target Server Version : 50721
File Encoding         : 65001

Date: 2018-04-18 17:20:53
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for conf_device
-- ----------------------------
DROP TABLE IF EXISTS `conf_device`;
CREATE TABLE `conf_device` (
  `DEV_ID` varchar(64) NOT NULL COMMENT '设备GUID, 不包括设备地域编码',
  `DISP_ZONE_ID` varchar(16) DEFAULT NULL COMMENT '调度分区',
  `DEV_IP` varchar(64) DEFAULT NULL COMMENT 'IP地址',
  `DEV_NAME` varchar(64) DEFAULT NULL COMMENT '设备名称（中文）',
  `DEV_INTERNAL_NAME` varchar(64) DEFAULT NULL COMMENT '内部名称',
  `HOST_NAME` varchar(64) DEFAULT NULL COMMENT '主机名',
  `VLEVEL_ID` varchar(8) DEFAULT NULL COMMENT '电压等级',
  `DEV_TYPE_ID` varchar(16) DEFAULT NULL COMMENT '设备类型',
  `PHY_POSITION` varchar(128) DEFAULT NULL COMMENT '物理位置',
  `MANUFACTURER_ID` varchar(64) DEFAULT NULL COMMENT '厂商信息的唯一标识',
  `DEV_MODEL` varchar(32) DEFAULT NULL COMMENT '设备型号',
  `GATHER_IP` varchar(64) DEFAULT NULL COMMENT '采集机IP',
  `SOFT_VERISON` varchar(32) DEFAULT NULL COMMENT '软件版本',
  `BUSINESS_SYSTEM` varchar(64) DEFAULT NULL COMMENT '所属业务系统',
  `DEV_PURPOSE` varchar(128) DEFAULT NULL COMMENT '设备用途',
  `MANAGER` varchar(16) DEFAULT NULL COMMENT '负责人',
  `PHONE_NUMBER` int(11) DEFAULT NULL COMMENT '联系电话',
  `CREATE_TIMESTAMP` datetime DEFAULT NULL COMMENT '创建时间',
  `MODIFY_TIMESTAMP` datetime DEFAULT NULL COMMENT '修改时间',
  `MEMO` varchar(255) DEFAULT NULL COMMENT '备注',
  PRIMARY KEY (`DEV_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of conf_device
-- ----------------------------

-- ----------------------------
-- Table structure for conf_device_if
-- ----------------------------
DROP TABLE IF EXISTS `conf_device_if`;
CREATE TABLE `conf_device_if` (
  `IF_ID` varchar(64) NOT NULL COMMENT '接口GUID，不包括地域编码',
  `IF_NAME` varchar(64) DEFAULT NULL COMMENT '接口名称',
  `IF_IP` varchar(64) DEFAULT NULL COMMENT '接口IP地址',
  `IF_MAC` varchar(32) DEFAULT NULL COMMENT '接口MAC地址',
  `DEV_ID` varchar(64) DEFAULT NULL,
  `MODIFY_TIMESTAMP` datetime DEFAULT NULL,
  PRIMARY KEY (`IF_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of conf_device_if
-- ----------------------------

-- ----------------------------
-- Table structure for conf_station
-- ----------------------------
DROP TABLE IF EXISTS `conf_station`;
CREATE TABLE `conf_station` (
  `STATION_ID` varchar(16) NOT NULL COMMENT '变电站编号，对应conf_device等表中的地域ID',
  `STATION_NAME` varchar(64) DEFAULT NULL COMMENT '变电站名称',
  `LOCATION_ID` varchar(16) DEFAULT NULL COMMENT '所属地区',
  `VLEVEL_ID` varchar(8) DEFAULT NULL,
  `STATION_TYPE_ID` int(11) DEFAULT NULL COMMENT '站点类型',
  PRIMARY KEY (`STATION_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of conf_station
-- ----------------------------
INSERT INTO `conf_station` VALUES ('03190001', '低涌变电站', '0319', '07', '1');

-- ----------------------------
-- Table structure for conf_topology
-- ----------------------------
DROP TABLE IF EXISTS `conf_topology`;
CREATE TABLE `conf_topology` (
  `TOPO_ID` varchar(64) NOT NULL COMMENT '唯一标识一条拓扑连接的GUID',
  `SRC_DEV_ID` varchar(64) DEFAULT NULL COMMENT '源端设备GUID',
  `SRC_DEV_COOR` varchar(32) DEFAULT NULL COMMENT '源端设备坐标，NULL',
  `SRC_IF_NAME` varchar(64) DEFAULT NULL COMMENT '接口名',
  `SRC_IF_MAC` varchar(32) DEFAULT NULL COMMENT '源物理端口IP',
  `SRC_IF_IP` varchar(64) DEFAULT NULL COMMENT '源物理端口IP地址',
  `SRC_IF_ONLINE` tinyint(4) DEFAULT NULL COMMENT '源物理端口IP在离线状态，1在线，0离线',
  `DST_DEV_ID` varchar(64) DEFAULT NULL COMMENT '目标设备GUID',
  `DST_DEV_COOR` varchar(32) DEFAULT NULL COMMENT '目标设备坐标',
  `DST_IF_NAME` varchar(64) DEFAULT NULL COMMENT '目标设备接口名',
  `DST_IF_MAC` varchar(32) DEFAULT NULL COMMENT '目标设备接口MAC地址',
  `DST_IF_IP` varchar(64) DEFAULT NULL COMMENT '目标设备接口IP地址',
  `DST_IF_ONLINE` tinyint(4) DEFAULT NULL COMMENT '目标设备接口在离线状态，1在线，0离线',
  `MODIFY_TIMESTAMP` datetime DEFAULT NULL COMMENT '拓扑连接改变时间戳',
  PRIMARY KEY (`TOPO_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of conf_topology
-- ----------------------------

-- ----------------------------
-- Table structure for dict_asset_legal
-- ----------------------------
DROP TABLE IF EXISTS `dict_asset_legal`;
CREATE TABLE `dict_asset_legal` (
  `ASSET_IS_LEGAL` varchar(4) DEFAULT NULL COMMENT '是否合法',
  `CODE` varchar(16) DEFAULT NULL COMMENT '编码'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of dict_asset_legal
-- ----------------------------
INSERT INTO `dict_asset_legal` VALUES ('是', 'legal');
INSERT INTO `dict_asset_legal` VALUES ('否', 'illegal');

-- ----------------------------
-- Table structure for dict_bussiness_sys_code
-- ----------------------------
DROP TABLE IF EXISTS `dict_bussiness_sys_code`;
CREATE TABLE `dict_bussiness_sys_code` (
  `SUB_SYSTEM` varchar(64) DEFAULT NULL COMMENT '子系统',
  `CODE` tinyint(4) DEFAULT '0' COMMENT '编码',
  `COMMONT` varchar(64) DEFAULT NULL COMMENT '说明'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of dict_bussiness_sys_code
-- ----------------------------
INSERT INTO `dict_bussiness_sys_code` VALUES ('基础资源平台（BRP）', '1', null);

-- ----------------------------
-- Table structure for dict_dev_type
-- ----------------------------
DROP TABLE IF EXISTS `dict_dev_type`;
CREATE TABLE `dict_dev_type` (
  `TYPE_ID` varchar(16) NOT NULL,
  `TYPE_NAME` varchar(64) NOT NULL DEFAULT '',
  PRIMARY KEY (`TYPE_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='设备类型';

-- ----------------------------
-- Records of dict_dev_type
-- ----------------------------
INSERT INTO `dict_dev_type` VALUES ('BID', '横向隔离装置（反向）');
INSERT INTO `dict_dev_type` VALUES ('DCD', '安全监测装置');
INSERT INTO `dict_dev_type` VALUES ('FID', '横向隔离装置（正向）');
INSERT INTO `dict_dev_type` VALUES ('FW', '防火墙');
INSERT INTO `dict_dev_type` VALUES ('MP', '平台');
INSERT INTO `dict_dev_type` VALUES ('PGE', '公用设备');
INSERT INTO `dict_dev_type` VALUES ('PSE', '二次设备');
INSERT INTO `dict_dev_type` VALUES ('SVR', '服务器');
INSERT INTO `dict_dev_type` VALUES ('SW', '交换机');
INSERT INTO `dict_dev_type` VALUES ('VEAD', '纵向加密装置');

-- ----------------------------
-- Table structure for dict_disp_level
-- ----------------------------
DROP TABLE IF EXISTS `dict_disp_level`;
CREATE TABLE `dict_disp_level` (
  `DISP_LEVEL_ID` varchar(8) NOT NULL,
  `DISP_LEVEL_NAME` varchar(32) DEFAULT NULL,
  PRIMARY KEY (`DISP_LEVEL_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of dict_disp_level
-- ----------------------------
INSERT INTO `dict_disp_level` VALUES ('11', '总调');
INSERT INTO `dict_disp_level` VALUES ('21', '中调');
INSERT INTO `dict_disp_level` VALUES ('31', '地调');
INSERT INTO `dict_disp_level` VALUES ('41', '县/区调');
INSERT INTO `dict_disp_level` VALUES ('51', '厂站');

-- ----------------------------
-- Table structure for dict_disp_zone
-- ----------------------------
DROP TABLE IF EXISTS `dict_disp_zone`;
CREATE TABLE `dict_disp_zone` (
  `ZONE_ID` varchar(16) NOT NULL,
  `ZONE_NAME` varchar(32) DEFAULT NULL,
  PRIMARY KEY (`ZONE_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of dict_disp_zone
-- ----------------------------
INSERT INTO `dict_disp_zone` VALUES ('I', 'I区');
INSERT INTO `dict_disp_zone` VALUES ('II', 'II区');
INSERT INTO `dict_disp_zone` VALUES ('III', 'III区');
INSERT INTO `dict_disp_zone` VALUES ('IV', 'IV区');
INSERT INTO `dict_disp_zone` VALUES ('V', 'V区');
INSERT INTO `dict_disp_zone` VALUES ('ZKC', '站控层');

-- ----------------------------
-- Table structure for dict_location
-- ----------------------------
DROP TABLE IF EXISTS `dict_location`;
CREATE TABLE `dict_location` (
  `LOCATION_ID` varchar(16) NOT NULL,
  `PARENT_ID` varchar(16) DEFAULT NULL,
  `LOCATION_NAME` varchar(32) DEFAULT NULL,
  PRIMARY KEY (`LOCATION_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of dict_location
-- ----------------------------
INSERT INTO `dict_location` VALUES ('00', null, '南网');
INSERT INTO `dict_location` VALUES ('0000', '00', '南网总调');
INSERT INTO `dict_location` VALUES ('03', null, '广东');
INSERT INTO `dict_location` VALUES ('0300', '03', '广东中调');
INSERT INTO `dict_location` VALUES ('0302', '03', '韶关地调');
INSERT INTO `dict_location` VALUES ('0304', '03', '珠海地调');
INSERT INTO `dict_location` VALUES ('0305', '03', '汕头地调');
INSERT INTO `dict_location` VALUES ('0306', '03', '佛山地调');
INSERT INTO `dict_location` VALUES ('0307', '03', '江门地调');
INSERT INTO `dict_location` VALUES ('0308', '03', '湛江地调');
INSERT INTO `dict_location` VALUES ('0309', '03', '茂名地调');
INSERT INTO `dict_location` VALUES ('0312', '03', '肇庆地调');
INSERT INTO `dict_location` VALUES ('0313', '03', '惠州地调');
INSERT INTO `dict_location` VALUES ('0314', '03', '梅州地调');
INSERT INTO `dict_location` VALUES ('0315', '03', '汕尾地调');
INSERT INTO `dict_location` VALUES ('0316', '03', '河源地调');
INSERT INTO `dict_location` VALUES ('0317', '03', '阳江地调');
INSERT INTO `dict_location` VALUES ('0318', '03', '清远地调');
INSERT INTO `dict_location` VALUES ('0319', '03', '东莞地调');
INSERT INTO `dict_location` VALUES ('0320', '03', '中山地调');
INSERT INTO `dict_location` VALUES ('0351', '03', '潮州地调');
INSERT INTO `dict_location` VALUES ('0352', '03', '揭阳地调');
INSERT INTO `dict_location` VALUES ('0353', '03', '云浮地调');
INSERT INTO `dict_location` VALUES ('04', null, '广西');
INSERT INTO `dict_location` VALUES ('0400', '04', '广西中调');
INSERT INTO `dict_location` VALUES ('05', null, '云南');
INSERT INTO `dict_location` VALUES ('0500', '05', '云南中调');
INSERT INTO `dict_location` VALUES ('06', null, '贵州');
INSERT INTO `dict_location` VALUES ('0600', '06', '贵州中调');
INSERT INTO `dict_location` VALUES ('07', null, '海南');
INSERT INTO `dict_location` VALUES ('0700', '07', '海南中调');
INSERT INTO `dict_location` VALUES ('08', null, '广州');
INSERT INTO `dict_location` VALUES ('0800', '08', '广州中调');
INSERT INTO `dict_location` VALUES ('09', null, '深圳');
INSERT INTO `dict_location` VALUES ('0900', '09', '深圳中调');

-- ----------------------------
-- Table structure for dict_manufacturer
-- ----------------------------
DROP TABLE IF EXISTS `dict_manufacturer`;
CREATE TABLE `dict_manufacturer` (
  `MANUFACTURER_ID` varchar(64) NOT NULL,
  `MANUFACTURER_NME` varchar(64) DEFAULT NULL,
  PRIMARY KEY (`MANUFACTURER_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of dict_manufacturer
-- ----------------------------

-- ----------------------------
-- Table structure for dict_net_identificate
-- ----------------------------
DROP TABLE IF EXISTS `dict_net_identificate`;
CREATE TABLE `dict_net_identificate` (
  `ZONE_NAME` varchar(8) NOT NULL COMMENT '分区',
  `ZONE_CODE` varchar(2) DEFAULT NULL COMMENT '编码'
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='分网标识';

-- ----------------------------
-- Records of dict_net_identificate
-- ----------------------------
INSERT INTO `dict_net_identificate` VALUES ('A网', 'A');
INSERT INTO `dict_net_identificate` VALUES ('B网', 'B');
INSERT INTO `dict_net_identificate` VALUES ('C网', 'C');

-- ----------------------------
-- Table structure for dict_net_port_status
-- ----------------------------
DROP TABLE IF EXISTS `dict_net_port_status`;
CREATE TABLE `dict_net_port_status` (
  `UP_DOWN_STATUS` varchar(8) DEFAULT NULL COMMENT 'up/down状态',
  `CODE` varchar(8) DEFAULT NULL COMMENT '编码'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of dict_net_port_status
-- ----------------------------

-- ----------------------------
-- Table structure for dict_on_off_status
-- ----------------------------
DROP TABLE IF EXISTS `dict_on_off_status`;
CREATE TABLE `dict_on_off_status` (
  `ON_OFF_STATUS` varchar(8) DEFAULT NULL COMMENT '在离线状态',
  `CODE` tinyint(2) NOT NULL DEFAULT '0' COMMENT '编码'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of dict_on_off_status
-- ----------------------------
INSERT INTO `dict_on_off_status` VALUES ('离线', '0');
INSERT INTO `dict_on_off_status` VALUES ('在线', '1');

-- ----------------------------
-- Table structure for dict_rule_type
-- ----------------------------
DROP TABLE IF EXISTS `dict_rule_type`;
CREATE TABLE `dict_rule_type` (
  `RULE_NAME` varchar(64) DEFAULT NULL COMMENT '规则名称',
  `RULE_NAME_CODE` tinyint(4) DEFAULT '0' COMMENT '规则名称编号',
  `EVENT_CONTENT` varchar(64) DEFAULT NULL COMMENT '事件内容',
  `EVENT_CONTENT_CODE` tinyint(4) DEFAULT '0' COMMENT '时间内容编码'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of dict_rule_type
-- ----------------------------
INSERT INTO `dict_rule_type` VALUES ('阈值监视', '1', '内存使用率数据库数据文件剩余空间不足', '1');
INSERT INTO `dict_rule_type` VALUES ('一般监视', '2', null, '0');
INSERT INTO `dict_rule_type` VALUES ('设备监视', '0', '敏感信息传输/流量信息', '3');
INSERT INTO `dict_rule_type` VALUES ('行为监视', '4', null, '0');

-- ----------------------------
-- Table structure for dict_station_type
-- ----------------------------
DROP TABLE IF EXISTS `dict_station_type`;
CREATE TABLE `dict_station_type` (
  `STATION_TYPE_ID` int(11) NOT NULL,
  `STATION_TYPE_NAME` varchar(32) DEFAULT NULL,
  PRIMARY KEY (`STATION_TYPE_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of dict_station_type
-- ----------------------------
INSERT INTO `dict_station_type` VALUES ('1', '系统变');
INSERT INTO `dict_station_type` VALUES ('2', '用户变');
INSERT INTO `dict_station_type` VALUES ('3', '统调电厂');
INSERT INTO `dict_station_type` VALUES ('4', '非统调电厂');
INSERT INTO `dict_station_type` VALUES ('5', '调度主站');

-- ----------------------------
-- Table structure for dict_voltage_level
-- ----------------------------
DROP TABLE IF EXISTS `dict_voltage_level`;
CREATE TABLE `dict_voltage_level` (
  `VLEVEL_ID` varchar(8) NOT NULL,
  `VLEVEL_NAME` varchar(64) DEFAULT NULL,
  PRIMARY KEY (`VLEVEL_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of dict_voltage_level
-- ----------------------------
INSERT INTO `dict_voltage_level` VALUES ('01', '交流110V');
INSERT INTO `dict_voltage_level` VALUES ('02', '交流220V');
INSERT INTO `dict_voltage_level` VALUES ('03', '交流380V');
INSERT INTO `dict_voltage_level` VALUES ('04', '交流660V');
INSERT INTO `dict_voltage_level` VALUES ('05', '交流1000V');
INSERT INTO `dict_voltage_level` VALUES ('06', '交流3kV');
INSERT INTO `dict_voltage_level` VALUES ('07', '交流6kV');

-- ----------------------------
-- Table structure for dict_warn_type
-- ----------------------------
DROP TABLE IF EXISTS `dict_warn_type`;
CREATE TABLE `dict_warn_type` (
  `INDEX` tinyint(4) NOT NULL DEFAULT '0' COMMENT '序号',
  `DEV_NAME` varchar(24) DEFAULT NULL COMMENT '设备',
  `LOG_TYPE` varchar(24) DEFAULT NULL COMMENT '日志类型',
  `LOG_TYPE_VAL` tinyint(4) NOT NULL DEFAULT '0' COMMENT '日志类型值',
  `SUB_LOG_TYPE` varchar(64) DEFAULT NULL COMMENT '日志类型名',
  `SUB_LOG_TYPE_VAL` tinyint(4) NOT NULL DEFAULT '0' COMMENT '日志子类型值',
  `WARN_TYPE` varchar(16) NOT NULL COMMENT '告警类型',
  `WARN_LEVEL` tinyint(4) NOT NULL DEFAULT '0' COMMENT '告警级别',
  `COMMENT` varchar(64) DEFAULT NULL COMMENT '备注',
  PRIMARY KEY (`LOG_TYPE_VAL`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='告警类型/日志类型/日志子类型';

-- ----------------------------
-- Records of dict_warn_type
-- ----------------------------
INSERT INTO `dict_warn_type` VALUES ('1', '交换机', '操作日志', '0', '用户登录', '1', '通过', '3', null);

-- ----------------------------
-- Table structure for dict_white_list
-- ----------------------------
DROP TABLE IF EXISTS `dict_white_list`;
CREATE TABLE `dict_white_list` (
  `WHITE_LIST_TYPE` varchar(24) DEFAULT NULL COMMENT '白名单类型',
  `CODE` tinyint(4) NOT NULL DEFAULT '0' COMMENT '编码'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of dict_white_list
-- ----------------------------
INSERT INTO `dict_white_list` VALUES ('通信白名单', '1');
INSERT INTO `dict_white_list` VALUES ('告警白名单', '2');
INSERT INTO `dict_white_list` VALUES ('主机白名单', '3');

-- ----------------------------
-- Table structure for dist_warn_level
-- ----------------------------
DROP TABLE IF EXISTS `dist_warn_level`;
CREATE TABLE `dist_warn_level` (
  `WARN_NAME` varchar(24) NOT NULL COMMENT '告警',
  `WARN_LEVEL` tinyint(4) NOT NULL DEFAULT '0' COMMENT '级别'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of dist_warn_level
-- ----------------------------
INSERT INTO `dist_warn_level` VALUES ('EMERG(紧急)', '0');
INSERT INTO `dist_warn_level` VALUES ('ERR(重要)', '1');
INSERT INTO `dist_warn_level` VALUES ('WARNNING(普通)', '2');
INSERT INTO `dist_warn_level` VALUES ('NOTICE(通告)', '3');
