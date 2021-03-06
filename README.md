Durian
======

评论与分享系统——榴莲  
你可以 __非商业目的__ 自由地下载/使用/修改源代码  
You are free to download/use/modify these codes for __non-commercial__ uses  

__演示视频__：http://v.youku.com/v_show/id_XNDk3MTA2MjE2.html  

===   
![Frame](https://raw.github.com/fanfank/durian/master/screenshots/durian_mainframe.jpg)  

###作品介绍
__请参见 *榴莲评论分享系统——说明文档.pdf* ，内有巨详细的介绍~！__  

###安装及部署
1. 可以在`./code`中可以修改一些默认设置：
> 在`./code/Durian.cpp`的第19行，修改FTP存储条目的根目录；  
> 在`./code/Durian.cpp`的第92行，93行，可以修改用以存储图片所在FTP的用户名及密码；而在第118行，119行可惜修改脱机使用
时的用户名及密码；  
> 在`./code/Durian.cpp`的第96行可以修改网络数据库的用户名，密码以及在第112行修改脱机状态下的用户名和密码；  
> 在`./code/AddressDlg.cpp`的第70行，71行，可以设定选择连接地址时默认填写的FTP地址及数据库地址；    
2. 使用Visual Studio 2012打开`./code/Durian.vcxproj`，若机器是32位，则在编译时选择 *Win32* ，否则进入配置，
在解决平台中新增 *x64* 。编译代码生成可执行文件。
3. 关于FTP及数据库的部署，请参见`./code/deploy/榴莲客户端项目部署文档.doc`。  

###使用
__请参见 *榴莲评论分享系统——说明文档.pdf* ，内有巨详细的介绍~！也可以直接观看顶部的演示视频~！__  

+ Git: fanfank
+ Code authors: 徐瑞琦，姜奕祺，萧浩源  
+ Contact email: reetsee.xu@gmail.com

<div class = "footer">
  &copy; 2013 Reetsee.Xu's Team
</div>

*README.md Last update: 20130819*
