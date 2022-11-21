# SNS3

卫星网络模拟器 3 (SNS3) 是网络模拟器 3 (ns-3) 平台的卫星网络扩展。


# License

SNS3 is distributed under the GPLv3 license.

# 安装手册（Installation Manual）

NS3 是作为 [NS3](https://www.nsnam.org/) 网络模拟器的扩展模块构建的。安装个人习惯waf安装
SNS3 is built as an extension module to the [NS3](https://www.nsnam.org/) network simulator; so their [installation instructions](https://www.nsnam.org/docs/release/3.29/tutorial/html/getting-started.html) apply, particularly concerning the dependencies. They are repeated here for convenience and proper integration of SNS3.

There are 2 methods to download and build (S)NS3:

*  the automated one using [bake](#bake);
*  the manual one using [waf](#waf).

## Bake

### Preparations


[Bake](http://planete.inria.fr/software/bake/index.html) is a tool developed to simplify the download and install process of NS3. It can be extended to make it aware of external modules to NS3 such as SNS3. You will first need to get bake.

First you need to download Bake using Git, go to where you want Bake to be installed and call 

```shell
$ git clone https://gitlab.com/nsnam/bake
```

It is advisable to add bake to your path

```shell
$ export BAKE_HOME=`pwd`/bake 
$ export PATH=$PATH:$BAKE_HOME
$ export PYTHONPATH=$PYTHONPATH:$BAKE_HOME
```

Before installing NS3, you will need to tell Bake how to find and download the SNS3 extension module. To do so, you will have to create a **contrib** folder inside the newly acquired **bake** folder:

```shell
$ cd bake
$ mkdir contrib
$ ls
bake  bakeconf.xml  bake.py  build  contrib  doc  examples  generate-binary.py  test  TODO
```


and drop the following file **sns3.xml** in this **contrib** folder:

```xml
<configuration>
  <modules>
    <module name="sns3-satellite" type="ns-contrib" min_version="ns-3.29">
      <source type="git">
        <attribute name="url" value="https://github.com/sns3/sns3-satellite.git"/>
        <attribute name="module_directory" value="satellite"/>
      </source>
      <build type="none">
      </build>
    </module>
    <module name="sns3-stats" type="ns-contrib" min_version="ns-3.29">
      <source type="git">
        <attribute name="url" value="https://github.com/sns3/stats.git"/>
        <attribute name="module_directory" value="magister-stats"/>
      </source>
      <build type="none">
      </build>
    </module>
    <module name="sns3-traffic" type="ns-contrib" min_version="ns-3.29">
      <source type="git">
        <attribute name="url" value="https://github.com/sns3/traffic.git" />
        <attribute name="module_directory" value="traffic"/>
      </source>
      <build type="none">
      </build>
    </module>
  </modules>
</configuration>
```
It might be necessary to remove the default bake configuration one in order to install sns3:
```shell
$ rm bakefile.xml
```

Now you’re ready to use bake.

### Installation

Now that everything is in place, you can tell bake that you want to install SNS3 (i.e.: ''ns-3'' plus the ''sns3-satellite'' module):

```shell
$ ./bake.py configure -e ns-3.29 -e sns3-satellite -e sns3-stats -e sns3-traffic
$ ./bake.py deploy
```

This will download the needed dependencies into a ''source'' folder and call the various build tools on each target. 
If bake finds that tools are missing on your system to download or build the various dependencies it will warn you 
and abort the build process if the dependency wasn't optional. You can ask bake for a summary of the required tools before deploying:

```shell
$ ./bake.py check
```

## Waf安装

安装NS3不做说明，SNS3模块需要'satellite'   'traffic'  'magister-stats'三个模块内容，将三个模块添加克隆进contrib目录

你将需要:

```shell
$ cd ns-3.29/contrib

$ git clone https://github.com/sns3/sns3-satellite.git satellite
$ git clone https://github.com/sns3/traffic.git traffic
$ git clone https://github.com/sns3/stats.git magister-stats
    
```
克隆3个模块后，从contrib目录进入satellite模块，进行子模块绑定（下载到data中,大约2G）。

```shell
$ git clone https://github.com/sns3/sns3-data.git data
```

然后，您需要配置 waf 并要求它构建 NS3。它将自动构建在 contrib 中找到的所有模块：

```shell
$ cd ns-3.29
$ ./waf configure -d optimized --enable-examples --enable-tests
$ ./waf build -j 6
```
也可以勾选waf选项，随意定制：


```shell
$ ./waf --help
```

