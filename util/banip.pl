#!/usr/bin/perl
# $Id$

@list = (
#bbsnet
'140.116.49.3', '163.23.212.5', '140.134.107.16', '134.208.3.64', '137.189.178.189', 
'140.134.107.16', '134.208.10.250', '211.151.95.188', '140.112.18.71', '140.123.107.90', 
'166.111.37.13', '206.222.17.254', '61.135.159.154', '210.51.188.45', '202.114.68.70', 
'140.116.49.3', '163.23.212.5', '140.116.246.180', '140.116.25.10', '202.207.208.100', 
'163.23.212.5', '211.151.89.114', '211.96.233.1', '202.205.80.137', '202.113.16.117',
# tor
'86.59.21.38', '149.9.137.153', '88.134.102.161', '24.170.55.120', '64.90.179.108', 
'88.112.243.180', '209.51.169.86', '213.114.29.49', '82.56.16.111', '141.76.46.90', 
'72.226.235.186', '64.5.53.220', '82.67.37.163', '83.243.88.133', '81.11.163.149', 
'85.178.254.218', '84.48.64.142', '69.136.226.204', '196.203.247.39', '66.91.243.239', 
'68.148.199.84', '84.172.127.88', '60.36.181.86', '71.32.251.76', '209.9.232.195', 
'83.233.97.253', '62.75.185.15', '80.202.104.135', '68.171.51.161', '67.68.0.144', 
'80.186.67.109', '217.119.47.6', '83.250.216.202', '207.210.101.242', '80.145.188.199', 
'68.202.36.79', '84.61.32.213', '81.57.158.21', '70.246.51.198', '208.40.218.136', 
'149.9.92.194', '219.95.23.216', '80.126.234.27', '221.118.188.140', '82.248.226.122',
'213.84.94.72', '80.126.37.100', '24.36.129.106', '64.136.200.11', '213.239.217.146',
'84.119.119.199', '66.90.118.68', '84.60.97.100', '213.132.141.91', '149.9.0.25',
'208.40.218.131', '213.228.241.143', '128.2.141.33', '18.187.1.68', '72.232.45.106',
'209.103.127.1', '213.112.22.232', '70.110.70.238', '140.78.95.135', '71.246.25.54',
'212.202.78.170', '24.111.174.178', '209.242.5.54', '81.169.176.135', '64.74.207.50',
'217.85.115.240', '62.75.218.208', '64.5.53.254', '87.105.54.221', '81.169.180.180',
'131.179.224.133', '82.66.155.32', '80.221.50.147', '194.29.137.67', '24.42.92.42',
'128.30.28.19', '217.160.109.40', '64.132.239.129', '212.114.250.252', '68.94.207.198',
'62.75.184.254', '207.44.180.3', '68.40.192.5', '217.160.167.28', '87.123.149.66',
'24.9.185.227', '68.174.141.133', '149.9.205.73', '217.160.203.26', '64.81.100.208',
'72.177.87.57', '81.169.158.102', '196.11.98.20', '69.41.174.196', '66.197.193.212',
'66.93.45.117', '70.156.79.236', '84.73.10.171', '59.134.15.153', '212.112.235.78',
'195.245.255.11', '213.133.99.185', '84.152.111.155', '81.216.157.211', '195.85.225.145',
'154.35.72.223', '85.16.11.120', '88.84.130.170', '88.113.36.247', '69.194.143.65',
'24.255.8.175', '150.140.191.108', '217.155.206.93', '128.2.132.175', '213.239.194.175',
'154.35.36.18', '84.34.133.217', '61.242.102.18', '217.84.135.45', '72.232.45.107',
'85.214.49.175', '84.9.35.164', '68.62.178.1', '70.92.178.34', '208.14.31.5',
'137.226.181.149', '69.249.105.136', '154.35.85.17', '72.20.1.166', '68.215.81.135',
'66.159.225.72', '66.236.18.180', '85.31.186.26', '69.31.42.139', '83.219.212.101',
'24.60.138.241', '213.113.166.243', '154.35.47.59', '80.222.227.120', '69.214.190.114',
'64.246.50.101', '217.172.49.89', '86.195.237.246', '24.27.135.128', '208.40.218.144',
'208.40.218.151', '83.64.135.124', '194.95.224.201', '216.231.168.178', '84.238.15.86',
'81.169.136.161', '68.166.71.225', '24.238.36.100', '84.57.65.203', '24.22.8.74',
'166.70.207.2', '82.46.18.28', '217.79.181.118', '24.155.82.33', '217.84.23.50',
'213.84.94.72', '149.9.25.222', '71.192.202.141', '89.110.144.180', '74.67.47.248',
'142.59.222.152', '213.84.192.84', '62.75.151.195', '213.239.206.174', '213.84.43.3',
'69.56.216.138', '70.187.87.248', '64.81.246.230', '80.252.209.6', '83.171.167.167',
'62.178.28.11', '83.171.154.26', '65.196.226.32', '85.31.187.84', '68.57.216.138',
'84.221.205.52', '65.174.217.58', '203.59.176.119', '217.20.117.240', '219.78.58.197',
'80.139.157.249', '87.14.241.155', '69.123.5.158', '83.194.181.199', '85.176.9.178',
'82.238.188.44', '84.16.234.153', '203.218.52.16', '81.169.130.130', '81.231.82.192',
'138.202.192.210', '217.147.80.73', '219.121.56.122', '81.5.172.97', '67.166.235.186',
'64.146.134.221', '72.0.207.216', '82.238.225.133', '64.90.164.74', '66.98.136.49',
'216.55.149.21', '198.161.91.196', '68.167.210.203', '192.42.113.248', '69.60.120.99',
'82.76.242.25', '212.112.242.21', '80.86.191.107', '129.21.228.86', '85.10.194.117',
'85.214.29.9', '24.250.192.233', '84.9.189.25', '72.165.204.124', '66.92.220.226',
'66.70.10.53', '82.165.180.112', '217.79.72.59', '129.187.150.131', '66.93.134.53',
'85.25.20.114', '62.194.151.17', '84.9.61.90', '85.10.226.188', '216.239.83.190',
'64.95.64.86', '195.72.0.6', '66.228.127.27', '68.167.210.88', '72.36.146.118',
'85.226.99.98', '80.203.211.14', '85.10.240.250', '72.3.249.87', '24.183.45.221',
'62.75.129.201', '70.28.148.123', '134.169.164.172', '84.221.71.186', '207.210.106.25',
'24.218.212.125', '213.203.214.130', '124.120.233.24', '62.163.136.55', '203.59.191.2',
'18.244.0.188', '69.110.16.109', '166.111.249.39', '85.214.26.137', '81.169.176.178',
'218.189.210.17', '216.237.143.47', '83.85.107.219', '216.9.82.85', '38.99.66.86',
'85.25.136.135', '129.21.144.211', '81.169.174.124', '212.239.118.83', '141.149.128.197',
'87.122.12.22', '82.231.59.44', '67.173.143.46', '80.242.195.68', '81.169.177.134',
'68.227.90.101', '216.39.146.25', '69.162.42.169', '82.82.71.189', '68.116.85.27',
'193.184.9.66', '84.56.188.25', '217.14.64.70', '217.160.170.132', '83.155.131.118',
'213.253.212.106', '80.137.90.161', '217.172.182.26', '68.113.150.180', '193.110.91.7',
'68.167.210.195', '20 6.174.19.25', '68.167.210.150', '66.52.66.26', '217.160.108.109',
'83.65.91.110', '85.25.132.119', '84.16.235.143', '24.6.177.106', '148.88.224.185',
'80.190.242.130', '84.179.37.99', '212.112.241.159', '207.210.85.116', '85.182.21.158',
'85.178.67.22', '81.227.234.84', '85.214.59.14', '80.237.146.62', '194.109.109.109',
'84.16.233.47', '64.142.31.83', '75.7.35.204', '64.126.160.82', '68.40.171.66',
'80.190.241.118', '142.59.97.101', '194.109.161.161', '84.55.87.137', '83.227.72.7',
'128.174.124.128', '216.32.80.75', '200.121.55.151', '195.158.167.131', '67.159.27.27',
'68.4.226.53', '217.153.252.4', '66.11.179.38', '70.128.40.144', '66.219.161.166',
'80.222.75.74', '83.171.161.111', '66.93.170.242', '66.210.104.251', '62.216.16.183',
'81.0.225.179', '64.34.180.99', '66.98.208.43', '84.73.181.254', '18.78.1.92',
'74.129.166.67', '213.220.233.15', '211.94.188.225', '24.91.169.157', '84.221.93.72',
'8.7.49.235', '84.157.194.20', '24.80.166.229', '82.156.33.125', '134.169.156.140',
'85.14.220.126', '71.245.115.23', '66.130.125.131', '82.165.253.73', '82.243.190.56',
'84.151.137.89', '88.191.22.62', '216.75.15.60', '80.74.148.176', '24.21.201.102',
'84.19.182.23', '69.148.137.24', '211.80.41.38', '70.235.64.97', '68.89.251.8',
'84.60.110.244', '81.190.201.225', '212.242.188.20', '201.50.46.196', '82.6.104.255',
'66.96.192.44', '70.226.164.81', '82.109.81.98', '65.101.98.113', '207.210.85.112',
'218.22.2.22', '62.197.40.155', '70.16.142.12', '64.122.12.107', '74.0.33.114',
'213.239.212.133', '84.154.134.88', '209.8.40.177', '212.112.241.137', '63.85.194.6',
'128.83.114.63', '24.178.205.107', '81.169.178.215', '72.225.234.118', '24.59.103.203',
'80.34.138.229', '140.247.60.64', '140.247.62.119', '18.152.2.242', '69.62.156.11',
'134.130.57.18', '80.190.251.24', '71.242.124.82', '80.190.242.122', '85.214.18.185',
'194.21.56.6', '85.178.118.33', '24.136.24.119', '85.227.10.132', '64.142.98.231',
'151.8.40.35', '88.73.64.70', '69.12.171.250', '71.133.227.217', '213.239.202.232',
'24.10.127.243', '217.28.206.143', '84.56.134.49', '216.137.65.86', '80.87.131.159',
'195.230.168.95', '88.84.139.250', '128.138.207.49', '88.191.12.200', '84.19.181.66',
'64.26.169.184', '71.120.32.3', '217.160.219.14', '84.220.99.237', '63.149.255.18',
'64.142.22.13', '80.127.66.162', '84.41.143.100', '82.165.144.169', '202.29.6.56',
'85.214.44.126', '72.21.33.202', '68.20.180.186', '85.10.195.106', '82.225.251.113',
'82.128.208.175', '204.253.162.11', '62.241.240.86', '70.127.121.248', '18.246.1.160',
'207.150.167.67', '155.207.113.227', '213.239.211.172', '81.56.27.175', '217.160.220.28',
'213.39.162.76', '80.244.242.127', '66.63.162.152', '70.84.114.153', '193.202.88.3',
'67.171.52.98', '87.89.99.153', '217.160.95.117', '69.113.27.92', '85.212.155.168',
'212.60.156.94', '217.160.177.118', '84.72.104.77', '85.31.186.86', '66.199.240.50',
'85.234.130.43', '71.56.235.157', '128.61.106.164', '62.75.171.154', '195.169.149.213',
'212.112.231.99', '212.112.235.83', '217.172.183.219', '69.163.32.140', '202.173.141.155',
'66.219.59.183', '82.94.251.206', '137.120.180.50', '70.81.159.32', '213.113.151.30',
'82.235.7.49', '213.114.177.134', '193.16.154.187', '64.230.63.177', '218.58.83.156',
'209.172.52.78', '69.12.145.165', '216.27.178.157', '64.62.190.126', '216.218.240.205',
'221.137.6.171', '209.221.193.39', '82.92.225.162', '82.149.72.85', '83.223.108.108',
'195.71.99.214', '208.99.207.139', '81.57.111.73', '195.158.168.91', '85.225.168.164',
'64.142.22.12', '213.100.254.195', '82.24.161.140', '66.199.252.58', '193.219.28.245',
'207.210.74.82', '68.146.1.177', '83.245.82.184', '204.15.133.171', '199.77.130.14',
'212.24.170.230', '212.202.233.2', '62.121.31.116', '147.251.52.140', '195.177.251.100',
'209.221.138.34', '209.114.200.129', '82.227.67.108', '88.198.253.18', '83.160.255.58',
'193.88.185.116', '24.11.233.143', '194.109.206.212', '85.214.29.61', '213.239.212.45',
'62.75.222.205', '212.112.242.159', '159.149.57.14', '66.92.188.226', '71.229.90.176',
'64.34.217.23', '18.244.0.114', '193.198.70.44', '18.244.0.188', '137.120.180.65',
'85.76.189.225', '88.112.63.167', '192.67.63.148', '140.247.62.64', '212.168.190.8',
'82.182.109.115', '213.146.114.96', '66.90.89.162', '80.223.105.208', '84.249.213.94',
'72.130.85.166', '85.8.136.101', '84.141.157.11', '217.160.132.150', '217.196.64.205',
'70.20.27.229', '217.160.176.49', '70.176.93.179', '208.66.194.6', '65.254.45.211',
'24.238.57.137', '80.237.206.93', '62.212.121.77', '68.229.206.234', '24.199.198.152',
'85.31.187.90', '64.142.78.232', '64.81.240.144', '213.113.27.69', '63.211.169.142',
'66.111.43.137', '222.212.62.102', '68.80.155.150', '130.161.165.129', '65.38.64.204',
'24.21.11.160', '67.177.13.99', '84.179.226.226', '24.202.5.70', '130.89.160.179',
'82.173.155.16', '86.56.26.161', '85.214.58.238', '166.70.232.84', '217.160.251.19',
'63.228.65.81', '68.127.89.54', '217.80.73.55', '69.203.21.27', '207.210.106.25',
'217.224.170.147', '216.254.98.195', '82.238.188.44', '168.150.251.36', '75.17.59.97',
'68.192.208.164', '207.55.224.210', '212.187.48.185', '24.185.154.23', '204.15.208.64',
'68.41.182.107', '24.127.236.10', '68.167.71.188', '64.4.231.146', '209.221.206.114',
'65.95.244.151', '212.7.12.43', '71.126.191.234', '217.85.76.76', '83.214.50.131',
'128.16.66.81', '87.123.108.76', '218.9.14.122', '212.202.43.223', '87.217.59.75',
'84.180.181.170', '83.233.34.183', '213.218.161.250', '84.160.97.247', '213.100.5.62',
'63.228.146.210', '85.210.1.124', '84.62.43.153', '69.148.137.24', '80.190.248.207',
'212.202.43.223', '84.148.43.128', '202.69.182.69');

print "const unsigned int banip[] = {";

foreach( @list ){
    $hash{(($1 * 256 + $2) * 256 + $3) * 256 + $4} = 1
	if( /^(\d+)\.(\d+)\.(\d+)\.(\d+)/ );

}
print scalar keys %hash, ",\n";

foreach (sort keys %hash) {
    print "${_}U,\t";
    print "\n" if ++$i % 4 == 0;
}

print "0};\n";
