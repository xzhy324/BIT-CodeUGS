#include "CMyString.h"
class CInternetURL{
private:
    CMyString data;
public:
    explicit CInternetURL(const CMyString& input):data(input){}
    explicit CInternetURL(const char* input):data(input){}
    CMyString GetDomain()const;
    CMyString GetDomainCountry()const;
    CMyString GetDomainType()const;
};

CMyString CInternetURL::GetDomain() const {
    CMyString res("");
    int p;
    if(data.Find("https://")==0)p=8;
    else if(data.Find("http://")==0)p=7;
    else p=0;

    while(data[p]!='\0'&&data[p]!='/') {
        res=res+data[p];
        p++;
    }
    return res;
}

CMyString CInternetURL::GetDomainCountry() const {
    CMyString domain=GetDomain();
    int dotPos;
    do{
        dotPos=domain.Find('.');
        domain=domain.Mid(dotPos+1,domain.size()-1);
    }while(dotPos!=-1);
    return domain;
}

CMyString CInternetURL::GetDomainType() const {
    CMyString domain=GetDomain();
    int dotPos=domain.FindBackwards('.');
    domain=domain.Mid(0,dotPos-1);
    dotPos=domain.FindBackwards('.');
    domain=domain.Mid(dotPos+1,domain.size()-1);
    return domain;
}