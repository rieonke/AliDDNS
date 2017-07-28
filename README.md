# AliDDNS
DDNS tool for AliYun

# 介绍
阿里云动态域名解析 aliddns 是适用于Linux/macOS/Unix(Windows未测试)平台的阿里云动态域名解析工具。

# 编译
1. 克隆代码到本地
```bash

git clone https://github.com/rieonke/AliDDNS.git
cd AliDDNS
git submodule init
git submodule update --recursive

```
2. 编译
```bash
cmake --build . --target aliddns
```

# 使用
1. 设置配置文件 config.json
```
{
  "Version": "1.0", // 阿里云API版本，不需要修改
  "AccessKeyId": "YOUR_KEY_ID_HERE", // 你的阿里云平台Access Key Id
  "AccessSecret" : "YOUR_SECRET_HERE", // 你的阿里云平台 Access Secret
  "Domain" : "example.com", // 需要解析的域名
  "Target" : "www", // 需要解析的目标域名
  "TTL" : "600" // TTL根据阿里云推荐设置即可
}

```

2. 启动
```bash

./aliddns

```
