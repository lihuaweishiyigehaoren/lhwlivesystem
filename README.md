# lhwlivesystem

该项目创建之初,作者想结合自己的课题搭建一个晚上的分布式生产车间管理系统,用现代化机器学习方法对生产产品进行实时质量管控,最后发现水平有限,很多东西自己既无法实现也无从借鉴,故出于个人爱好,多方借鉴,搭建一个小小的直播系统.

## 直播系统架构

![avatar](./dos/picture/总体架构.png)

### 概述

个人认为，我通过借鉴他人架构搭建的spider网络架构并不适用于直播系统.

>spider是基于TCP/IP协议搭建,面向连接的流传输为了保证消息的正确传输,需要维护连接.
>
>而直播系统中,观众的写很频繁,对于想发弹幕这种行为,因为一个直播间可能会有成千上万条弹幕,丢了极小一部分也就丢了,对系统和客户体验并不会产生太大的影响,因此选择UDP的通信方式可能会更好一些

但是作者为了对C/S有一个形象、系统的认识，依然选择用它来搭建一个直播系统。

### 客户层

在客户层，主要由房主（主播）和观众两类人，根据权限的不同，观众里还有房管和普通观众之分，他们拥有自己的权限和职责。客户层主要与服务层交互，弹幕等。

### 服务层

服务层的义务则比较多，客户端的上下线，弹幕的筛选等等。同时也是客户端与存储层交流的桥梁。

### 存储层

存储层会使用MySql存储用户的注册信息，同时由于刷礼物的榜单更新的速率非常快，使用数据库读取效率非常低，因此使用redis作为缓存。



## 系统版本测试(1.0.0)

### spider网络库测试