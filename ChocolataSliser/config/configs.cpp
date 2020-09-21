#include "configs.hpp"

template<typename... _Tp> struct visitor : _Tp... { using _Tp::operator()...; };
template<typename... _Tp> visitor(_Tp...) -> visitor<_Tp...>;

void Configs::validate() noexcept
{
    for(auto [name, value] : configs)
      std::visit ( visitor
        {
          [&] (ParamType<   Boolean  >* param) { if(param->isChanged()) param->check(); },
          [&] (ParamType< Value<int> >* param) { if(param->isChanged()) param->check(); },
          [&] (ParamType<Value<float>>* param) { if(param->isChanged()) param->check(); }
        }, value );
}

void Configs::open(std::string path) noexcept
{
    std::ifstream in(path, std::ios::binary);
    for(auto [name, value] : configs)
    {
        uint32_t size;
        in.read((char*)&size, 4);
        std::visit ( visitor
          {
            [&] (ParamType<   Boolean  >* param) { in.read((char*)param, size); },
            [&] (ParamType< Value<int> >* param) { in.read((char*)param, size); },
            [&] (ParamType<Value<float>>* param) { in.read((char*)param, size); }
          }, value );
    }
}

void Configs::save(std::string path) noexcept
{
    std::ofstream out(path, std::ios::binary);
    for(auto [name, value] : configs)
    {
        std::visit ( visitor
          {
            [&] (ParamType<   Boolean  >* param)
                { uint32_t size = sizeof(*param); out.write((char*)&size, 4); out.write((char*)param, size); },
            [&] (ParamType< Value<int> >* param)
                { uint32_t size = sizeof(*param); out.write((char*)&size, 4); out.write((char*)param, size); },
            [&] (ParamType<Value<float>>* param)
                { uint32_t size = sizeof(*param); out.write((char*)&size, 4); out.write((char*)param, size); }
          }, value );
    }
}
