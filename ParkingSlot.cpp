#include <bits/stdc++.h>
using namespace std;

enum VehicleType
{
    SMALL,
    MEDIUM,
    LARGE
};

class Vehicle
{
    private:
    string owner;
    string vehicleNumber;
    VehicleType vtype;
    public:
    Vehicle(string owner_,string vehicleNumber_,VehicleType vtype_)
    {
        owner=owner_;
        vtype=vtype_;
        vehicleNumber=vehicleNumber_;
    }
    VehicleType getVechileType()
    {
        return vtype;
    }
};

class ParkingSlot
{
    private:
    VehicleType vtype;
    Vehicle* voccupied; 
    int Start;
    public:
    ParkingSlot(VehicleType vtype_)
    {
        vtype=vtype_;
        voccupied=NULL;
        Start=0;
    }
    void addVehicle(Vehicle* toAdd,int st)
    {
        voccupied=toAdd;
        Start=st;
        return ;
    }
    int FreeSlot(int curTime)
    {
        voccupied=NULL;
        return curTime-Start;
    }
    bool isAvailable()
    {
        return voccupied==NULL;
    }
    Vehicle* getVehicle()
    {
        return voccupied;
    }
    VehicleType getVechileType()
    {
        return vtype;
    }
};

class ParkingLot
{
    private:
    vector<ParkingSlot*> vParkingSlot;
    public:
    ParkingLot(){}

    void addSlot(ParkingSlot* toAdd)
    {
        vParkingSlot.push_back(toAdd);
    }
    bool checkAvailablity(Vehicle* vehicle)
    {
        for(auto itr:vParkingSlot)
        {
            if(itr->isAvailable() && itr->getVechileType()==vehicle->getVechileType())
            {
                return true;
            }
        }
        return false;
    }
    int exit(Vehicle* vehicle,int time)
    {
        for(auto itr:vParkingSlot)
        {
            if(itr->getVehicle()==vehicle)
            {
                return itr->FreeSlot(time);
            }
        }
    }
    void assignSlot(Vehicle* toAdd,int curTime)
    {
        for(auto itr:vParkingSlot)
        {
            if(itr->isAvailable())
            {
                itr->addVehicle(toAdd,curTime);
                break;
            }
        }
    }
};

int main() 
{
    Vehicle* v1 = new Vehicle("Zaid","1234",SMALL);
    Vehicle* v2 = new Vehicle("Kaif","9867",MEDIUM);
    ParkingSlot* pslot1 = new ParkingSlot(SMALL);
    ParkingSlot* pslot2 = new ParkingSlot(MEDIUM);
    ParkingLot* plot = new ParkingLot();
    plot->addSlot(pslot1);
    plot->addSlot(pslot2);
    // cout<<plot->checkAvailablity(v1)<<endl;
    if(plot->checkAvailablity(v1))
        plot->assignSlot(v1,1);
    cout<<plot->exit(v1,4);
    // cout<<plot->checkAvailablity(v1);
    return 0;
}
