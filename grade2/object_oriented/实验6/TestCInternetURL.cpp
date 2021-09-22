#include "CInternetURL.h"
int main(){
    CInternetURL url("https://www.bit.edu.cn/xww/lgxb21/067aaa91b7524e7f9a43a5263633fcf4.htm");
    cout<<url.GetDomain()<<endl;
    cout<<url.GetDomainCountry()<<endl;
    cout<<url.GetDomainType()<<endl;
    return 0;
}