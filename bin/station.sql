/*
MySQL Data Transfer
Source Host: localhost
Source Database: station
Target Host: localhost
Target Database: station
Date: 8/20/2007 2:20:53 AM
*/

SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for accounts
-- ----------------------------
CREATE TABLE `accounts` (
  `id` mediumint(8) unsigned NOT NULL auto_increment,
  `username` varchar(32) character set utf8 collate utf8_unicode_ci NOT NULL,
  `password` varchar(40) character set utf8 collate utf8_unicode_ci NOT NULL,
  `email` varchar(255) character set utf8 collate utf8_unicode_ci NOT NULL,
  `salt` varchar(3) collate latin1_general_ci NOT NULL,
  `created_on` datetime NOT NULL,
  `last_login` timestamp NOT NULL default '0000-00-00 00:00:00' on update CURRENT_TIMESTAMP,
  `status` tinyint(1) NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=507 DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

-- ----------------------------
-- Table structure for characters
-- ----------------------------
CREATE TABLE `characters` (
  `id` mediumint(8) NOT NULL auto_increment,
  `account_id` mediumint(8) NOT NULL,
  `galaxy_id` mediumint(8) NOT NULL,
  `zone_id` mediumint(8) NOT NULL,
  `object_id` bigint(20) NOT NULL,
  `cell_id` bigint(20) NOT NULL DEFAULT 0,
  `firstname` varchar(255) collate latin1_general_ci NOT NULL,
  `surname` varchar(35) collate latin1_general_ci default NULL,
  `model` varchar(255) collate latin1_general_ci NOT NULL,
  `category` varchar(64) collate latin1_general_ci NOT NULL,
  `type` varchar(64) collate latin1_general_ci NOT NULL,
  `appearance` blob NOT NULL,
  `hair` varchar(255) collate latin1_general_ci NOT NULL,
  `hair_data` blob NOT NULL,
  `biography` text collate latin1_general_ci NOT NULL,
  `mood` varchar(64) collate latin1_general_ci NOT NULL default 'none',
  `credits_bank` bigint(20) NOT NULL DEFAULT 0,
  `credits_inventory` bigint(20) NOT NULL DEFAULT 0,
  `health` int(11) NOT NULL,
  `strength` int(11) NOT NULL,
  `constitution` int(11) NOT NULL,
  `action` int(11) NOT NULL,
  `quickness` int(11) NOT NULL,
  `stamina` int(11) NOT NULL,
  `mind` int(11) NOT NULL,
  `focus` int(11) NOT NULL,
  `willpower` int(11) NOT NULL,
  `health_wounds` int(11) NOT NULL DEFAULT 0,
  `strength_wounds` int(11) NOT NULL DEFAULT 0,
  `constitution_wounds` int(11) NOT NULL DEFAULT 0,
  `action_wounds` int(11) NOT NULL DEFAULT 0,
  `quickness_wounds` int(11) NOT NULL DEFAULT 0,
  `stamina_wounds` int(11) NOT NULL DEFAULT 0,
  `mind_wounds` int(11) NOT NULL DEFAULT 0,
  `focus_wounds` int(11) NOT NULL DEFAULT 0,
  `willpower_wounds` int(11) NOT NULL DEFAULT 0,
  `battle_fatigue` int(11) NOT NULL DEFAULT 0,
  `creature_type` bigint(20) NOT NULL DEFAULT 0,
  `faction_alignment` bigint(20) NOT NULL DEFAULT 0,
  `planet` varchar(32) collate latin1_general_ci NOT NULL,
  `quaternion_x` float NOT NULL,
  `quaternion_y` float NOT NULL,
  `quaternion_z` float NOT NULL,
  `quaternion_w` float NOT NULL,
  `position_x` float NOT NULL,
  `position_y` float NOT NULL,
  `position_z` float NOT NULL,
  `scale` float NOT NULL,
  `created_on` datetime NOT NULL,
  `last_updated` timestamp NOT NULL default '0000-00-00 00:00:00' on update CURRENT_TIMESTAMP,
  `state` int(11) NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

-- ----------------------------
-- Table structure for galaxies
-- ----------------------------
CREATE TABLE `galaxies` (
  `id` mediumint(8) NOT NULL auto_increment,
  `name` varchar(64) collate latin1_general_ci NOT NULL,
  `version` tinyint(1) NOT NULL,
  `max_capacity` mediumint(8) NOT NULL,
  `status` tinyint(1) NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=2 DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

-- ----------------------------
-- Table structure for servers
-- ----------------------------
CREATE TABLE `servers` (
  `id` mediumint(8) NOT NULL auto_increment,
  `galaxy_id` mediumint(8) NOT NULL,
  `type` tinyint(2) NOT NULL,
  `address` varchar(16) collate latin1_general_ci NOT NULL,
  `admin_port` mediumint(8) NOT NULL,
  `client_port` mediumint(8) NOT NULL,
  `comm_port` mediumint(8) NOT NULL,
  `ping_port` mediumint(8) NOT NULL,
  `population` tinyint(4) NOT NULL,
  `status` tinyint(1) NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=5 DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

-- ----------------------------
-- Records 
-- ----------------------------
INSERT INTO `accounts` VALUES ('506', 'test', '90063f9f1879ae25adad66ddd3f91097', 'test@test.com', 'ade', '2007-07-15 15:19:39', '0000-00-00 00:00:00', '1');
INSERT INTO `galaxies` VALUES ('1', 'Naritus', '0', '10', '2');
INSERT INTO `servers` VALUES ('1', '1', '2', '127.0.0.1', '0', '44453', '4447', '0', '0', '2');
INSERT INTO `servers` VALUES ('2', '1', '0', '127.0.0.1', '0', '44463', '4448', '44462', '10', '2');
INSERT INTO `servers` VALUES ('3', '1', '3', '127.0.0.1', '0', '0', '4449', '0', '0', '2');
