#include <iostream>
#include <set>
#include <vector>
#include <map>

using namespace std;
using std::set;
using std::vector;
using std::map;
typedef set<int> IntSet;
typedef vector<int> TVecDWORD;

typedef const vector<vector<TVecDWORD>> TVecMatchInfoCFG;
typedef int DWORD;
const map<int,TVecMatchInfoCFG> MAP_PROFESSION_MATCHINFO = {
  {411,
    {
      // 1只队伍
      //{{411}},
      // 2只队伍
      {
       {100,311},{10,401},{1,410},
       {110,301},{101,310},{11,400},{200,211},
       {300,111},{201,210},
      },
      // 3只队伍
      {
        {400,10,1},{310,100,1},{301,100,10},{211,100,100},

        {100,110,201},{100,101,210},{100,11,300},{100,200,111},
        {10,101,300},{10,200,201},{1,110,300},{1,200,210},

        {110,101,200},{11,200,200},
      },
      // 4只队伍
      {
        {300,100,10,1},{201,100,100,10},{210,100,100,1},{111,100,100,100},
        {110,101,100,100},{110,200,100,1},{101,200,100,10},{200,200,1,10},
      },
      // 5只队伍
      {
        {110,100,100,100,1},{101,100,100,100,10},{11,100,100,100,100},{200,100,100,10,1},
      },
      // 6只队伍
      {
        {100,100,100,100,10,1},
      },
    }
  },

  {222,
    {
      // 1只队伍
      //{{222}},
      // 2只队伍
      {
        {100,122},{10,212},{1,221},
        {200,22},{20,202},{2,220},{110,112},{101,121},{11,211},
        {111,111},{210,12},{201,21},{120,102},
      },
      // 3只队伍
      {
        {100,10,112},{100,1,121},{10,1,211},{100,100,22},{10,10,202},{1,1,220},

        {100,110,12},{100,101,21},{100,11,111},{100,20,102},{100,2,120},
        {10,110,102},{10,101,111},{10,11,201},{10,200,12},{10,2,210},
        {1,110,111},{1,101,120},{1,11,210},{1,200,21},{1,20,201},

        {200,20,2},{200,11,11},{20,101,101},{2,110,110},{110,101,11},
      },
      // 4只队伍
      {
        {210,10,1,1},{201,10,10,1},{120,100,1,1},
        {102,100,10,10},{21,100,100,1},{12,100,100,10},

        {200,20,1,1},{200,2,10,10},{20,2,100,100},
        {110,110,1,1},{101,101,10,10},{11,11,100,100},
        {110,101,10,1},{110,11,100,1},{101,11,100,10},
      },
      // 5只队伍
      {
        {200,10,10,1,1},{20,100,100,1,1},{2,100,100,10,10},
        {110,100,10,1,1},{101,100,10,10,1},{11,100,100,10,1},
      },
      // 6只队伍
      {
        {100,100,10,10,1,1},
      },
    }
  }
};
int main(int argc,char*argv[])
{
  /*
  char* testType = argc > 1 ? argv[1] : NULL;
  //cout << argc << " " << *testType << endl;
  enum ET
  {
    E0 = 0,
    E1 = 1,
    E2 = 2,
  };
  ET e = E0;
  if (testType)
  {
    switch(*testType)
    {
      case '1':
        e = E1;
        break;
      case '2':
        e = E2;
        break;
      default:
        break;
    }
  }
  */

  auto func = [&](int n)
  {
    auto it1 = MAP_PROFESSION_MATCHINFO.find(n);
    for (auto &v : it1->second)
    {
      for (auto &v1 : v)
      {
        int sum = 0;
        for (auto &v2 : v1)
        {
          sum+=v2;
        }
        if (sum != n)
        {
          for (auto &v2 : v1)
            cout << v2 << " ";
          cout << "= " << sum << endl;
        }
      }
    }
  };
  func(411);
  func(222);

  map<DWORD, vector<map<DWORD,DWORD>>> MAP_MATCH_INFO;
  auto it = MAP_PROFESSION_MATCHINFO.find(222);
  auto& vecData = it->second;
  for (auto &v : vecData)
  {
    for (auto &v1 : v)
    {
      // v1 = {100,311}, v1 = {111,100,100,100},
      map<DWORD,DWORD> mmap;
      IntSet vset;
      for (auto &v2 : v1)
      {
        mmap[v2]++;
        vset.insert(v2);
      }

      for (auto &v2 : vset)
      {
        map<DWORD, DWORD> rmap = mmap;
        auto mm = rmap.find(v2);
        if (mm->second > 1)
        {
          mm->second -= 1;
        }
        else
        {
          rmap.erase(mm);
        }

        MAP_MATCH_INFO[v2].push_back(rmap);
      }
    }
  }

  for (auto &m: MAP_MATCH_INFO)
  {
    cout << "匹配 " << m.first << " 如下------------------------------------:"<< endl;

    for (auto &v : m.second)
    {
      for (auto &m1 : v)
      {
        cout << "编号:" << m1.first << " 个数: " << m1.second << endl;
      }
      cout << "----" << endl;
    }
  }

  return 0;
}
