/*
1.为了满足用户对快递运费和实效的不同需求，某快递公司根据海运、陆地、空运三种不同的快递运输交通工具的运输成本以及运输距离，
 制定了相应的收费标准如下：
海运运费 ＝ 路程距离 × W11 ＋ 货物重量 × W12 + 10
陆地运费 ＝ 路程距离 × W21 ＋ 货物重量 × W22 + 30
空运运费 ＝ 路程距离 × W31 ＋ 货物重量 × W32 + 60
其中，Wij（i = 1，2，3；j = 1，2）是不同交通工具在路程距离和货物重量的权重，分别取值为
 （1.05，0.95）、（1.25，1.1）和（1.55，1.3）。
请根据快递公司制定的标准，设计类并实现快递费用的计算。
 */

#include <iostream>
using namespace std;
class CVehicle
{
public:
// 通过构造函数设置运输工具在路程距离和货物重量的权值
    CVehicle(double paraDistance, double paraWeight)
    {
        SetParameters(paraDistance, paraWeight);
    }

    virtual ~CVehicle(){  cout << "~CVehicle" << endl;  };

    // 设置运输工具路程距离和货物重量的权值
    void SetParameters(double paraDistance, double paraWeight)
    {
        m_dParaDistance = paraDistance;
        m_dParaWeight = paraWeight;
    }

    // 运输费用计算的统一接口
    virtual double Freight(double distance, double weight) = 0;
protected:
    double m_dParaDistance, m_dParaWeight;      // 路程距离和重量对应的权重
};

class CShip : public CVehicle{
public:
    CShip(double paraDistance, double paraWeight):CVehicle(paraDistance,paraWeight){}
    ~CShip(){cout<<"~CShip"<<endl;}
    virtual double Freight(double distance, double weight){
        return distance*m_dParaDistance + weight*m_dParaWeight + 10;
    }
};

class CTruck : public CVehicle{
public:
    CTruck(double paraDistance, double paraWeight):CVehicle(paraDistance,paraWeight){}
    ~CTruck(){cout<<"~CTruck"<<endl;}
    virtual double Freight(double distance, double weight){
        return distance*m_dParaDistance + weight*m_dParaWeight + 30;
    }
};

class CPlane : public CVehicle{
public:
    CPlane(double paraDistance, double paraWeight):CVehicle(paraDistance,paraWeight){}
    ~CPlane(){cout<<"~CPlane"<<endl;}
    virtual double Freight(double distance, double weight){
        return distance*m_dParaDistance + weight*m_dParaWeight + 60;
    }
};

class CFreight{
private:
    CVehicle *v;
public:
    void SetVehicle(CVehicle *i){
        v=i;
    }
    double GetPrice(double distance,double weight){
        return v->Freight(distance,weight);
    }
};

int main()
{
    CVehicle *vehicle[3];
    // 动态生成三个派生类对象
    vehicle[0] = new CShip(1.05, 0.95);
    vehicle[1] = new CTruck(1.25, 1.1);
    vehicle[2] = new CPlane(1.55, 1.3);
    CFreight freight;
    for (int i = 0; i<3; i++)
    {
        // 设置不同的运输工具对象，这些对象以统一的运输费用接口方式来访问
        freight.SetVehicle(vehicle[i]);
        cout << typeid(*vehicle[i]).name() << "：" << freight.GetPrice(1000, 20)<<endl;
    }
    // 释放动态生成的对象
    for (int i=0; i<3; i++)
    {
        if (vehicle[i] != nullptr)  delete vehicle[i];
    }
}