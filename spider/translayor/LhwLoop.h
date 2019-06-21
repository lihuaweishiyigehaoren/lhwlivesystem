/**
* @version 1.0.0
* @author lihuawei
* @mail lihuawei@hust.edu.cn
* @see https://github.com/lihuaweishiyigehaoren/lhwlivesystem
* @file LhwLoop.h
* lhwlivesystem第一版本发布
* 版本号1.0.0
*/


#pragma once

namespace translayor
{
    class LhwLoop
    {
    public:
        virtual ~LhwLoop(){}

        void Start() 
        {
            _run();
        }

    protected:
        virtual void _run()=0;
    };
}