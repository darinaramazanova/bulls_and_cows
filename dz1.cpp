#include <iostream>
#include <ctime>
#include <vector>
#include <array>
#include <cmath>
#include <string>
#include <algorithm>

const int bot_win = 2;
const int user_win =1;
struct num{

    std::array<int, 4> full;
    num(int a){

        update(a);
    }

    void update(int a){
        for (int i{0}; i < 4; ++i){
            full[i] = a / static_cast<int>(pow(10, full.size() - 1 - i)) % 10;
        }
    }
    bool validate()
    {
        for (int i{0}; i<4; ++i)
        {
            for (int j{i+1}; j<4; ++j)
            {
                if (full[i] == full[j])
                {
                    return false;
                }

            }
        }
        return true;
    }
    std::string tostring()
    {
        std::string s;
        for (int i{0}; i<4; ++i)
        {
            s+=std::to_string(full[i]);
        }
        return s;
    }
    bool operator==(const num& other)
    {
        for(int i{0}; i<4; ++i)
        {
            if (full[i] !=other.full[i])
            {
                return false;
            }
        }
        return true;
    }
};

int get_random_number()
{
    return rand() % (9998+2);

}
struct solver
{
    solver() = default;
    std::vector<num> falsenums;
    num cnum{1234};
    std::string do_prediction()
    {
        while (find(falsenums.begin(), falsenums.end(),cnum)!=falsenums.end())
        {
            cnum.update(get_random_number());
            while (!cnum.validate())
            {
                cnum.update(get_random_number());   
            }
        }

        falsenums.push_back(cnum);
        return cnum.tostring();   
    }
};

void countcoeffs(std::array<int,2>& coeffs, num rnum, num compnum)
{
    coeffs[0] = 0;
    coeffs[1] = 0;

    for (int i{0}; i<4; ++i)
    {
        for (int j{0}; j<4; ++j)
        {
            if (rnum.full[i] == compnum.full[j])
            {
                if (i==j)
                {
                    ++coeffs[0];
                }
                else
                {
                    ++coeffs[1];
                }
            }
        }
    }
}

void game(){
    int gameisover{0}; 
    std::array<int, 2> coeffs{0,0};
    solver bot{};

    num botnum{get_random_number()};
    while (!botnum.validate())
    {
        botnum.update(get_random_number());
    }


    std::cout<<"bulls and cows game"<< std::endl;
    int movenum = 1;
    while (!gameisover)
    {
        std::cout<<"Move "<< movenum <<". Your move: ";
        unsigned int userguessnumraw{0};
        std::cin>>userguessnumraw;
        if (userguessnumraw > 9999)
        {
            std::cout << "invalid"<<std::endl;
            continue;
        }
        num userguessnum{userguessnumraw};
        if (!userguessnum.validate())
        {
           std::cout << "invalid"<<std::endl;
            continue; 
        }
        countcoeffs(coeffs, botnum, userguessnum);
        ++movenum;
        if (coeffs[0]==4)
        {
            gameisover=1;
            std::cout<<"you win!"<<std::endl;
        }
        if (gameisover != user_won)
        {
            std::cout <<"Bulls: "<<coeffs[0]<<", cows: "<<coeffs[1]<<std::endl;
        }
        std::cout<<"My move. Is it "<<bot.do_prediction() <<"?(y/n): ";
        while(true)
        {
            std::string t;
            std::cin>>t;
            if (t =="y")
            {
                gameisover = bot_won;
                std::cout<<"bot win, you loser"<<std::endl;
                return;
            }
            if (t=="n")
            {
                break;
            }
            std::cout<<"user invalid. (y/n): ";
        }
        if (gameisover != bot_won)
        {
            if (gameisover == user_won)
            {
                std::cout<<"you win!"<<std::endl;
                return;
            }
            std::array<int,2>botcoeffs{0, 0};
            std::cout<<"Bulls: ";
            std::cin>>botcoeffs[0];
            std::cout<<"Cows: ";
            std::cin>>botcoeffs[1];
        }


    }
}
int main()
{
    srand(time(0));
    game();

    return 0;

}

