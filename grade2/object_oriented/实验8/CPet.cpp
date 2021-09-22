#include "iostream"

using namespace std;

class pet{
public:
    virtual void tune()const{
        cout<< typeid(*this).name()<<":"<<"tune()!\n";
    }
};

class dog : public pet{
public:
    virtual void tune()const{
        cout<<typeid(*this).name()<<" : "<<"wang!\n";
    }
};

class cat : public pet{
public:
    virtual void tune()const{
        cout<<typeid(*this).name()<<" : "<<"miao!\n";
    }
};

class sparrow : public pet{
public:
    virtual void tune()const{
        cout<<typeid(*this).name()<<" : "<<"hello,hello!\n";
    }
};

class family{
private:
    pet *our_pets[10];
    int pet_amount;
public:
    family():pet_amount(0){}
    bool add_pet(pet* new_pet){
        if(pet_amount>10)return false;
        our_pets[pet_amount++] = new_pet;
        return true;
    }

    void Lets_Tune()const{
        for(int i=0;i<pet_amount;i++){
            our_pets[i]->tune();
        }
    }

    void ShowOurPets()const{
        int cat_n=0,dog_n=0,sparrow_n=0;
        for(int i=0;i<pet_amount;i++){
            if( typeid(*our_pets[i]) == typeid(dog) )dog_n++;
            if( typeid(*our_pets[i]) == typeid(cat) )cat_n++;
            if( typeid(*our_pets[i]) == typeid(sparrow) )sparrow_n++;
        }
        printf("we have dog %d,cat %d,sparrow %d\n",dog_n,cat_n,sparrow_n);
    }
};


int main(){
    family F;
    F.add_pet(new dog);
    F.add_pet(new dog);
    F.add_pet(new cat);
    F.add_pet(new sparrow);
    F.Lets_Tune();
    F.ShowOurPets();
}