#pragma once

namespace translayor
{
    class Loop
    {
    public:
        virtual ~Loop(){}

        void Start() 
        {
            _Run();
        }

    protected:
        virtual void _Run()=0;
    };
}