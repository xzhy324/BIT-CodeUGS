#include <windows.h>
#include <iostream>
#include <psapi.h>
#include <tlhelp32.h>
#include <shlwapi.h>
#include <cstring>

#define Gsize 1073741824
#define Ksize 1024
using namespace std;

void getMemoryInfo(){
    MEMORYSTATUSEX memoryStatus;
    memoryStatus.dwLength = sizeof(memoryStatus); //需要提前设定，否则不能使用结构体
    GlobalMemoryStatusEx(&memoryStatus);
    //实际物理内存的大小（单位：字节）
    printf("DRAM total capability : %.2f GB \n",
           (float)memoryStatus.ullTotalPhys/Gsize);
    //现在可用的物理内存大小（单位：字节）这部分物理内存是可以不需要写入磁盘立即被回收的内存。
    //它是备用，空闲和零列表大小的综合
    printf("DRAM available capability : %.2f GB \n",
           (float)memoryStatus.ullAvailPhys/Gsize);
    //物理内存使用的百分比（从0到100）
    printf("DRAM usage : %ld %% \n",
           (long)memoryStatus.dwMemoryLoad);
    //系统或当前进程已经提交的内存限制中的较小者（单位：字节）。
    printf("Total space of page files : %.3g GB \n",
           (float)memoryStatus.ullTotalPageFile/Gsize);
    //当前进程可以提交的最大内存量
    printf("Available space of page files : %.3g GB \n",
           (float)memoryStatus.ullAvailPageFile/Gsize);
    //调用进程的虚拟地址空间的用户模式部分的大小（单位：字节）。
    // 此值取决于进程类型，处理机类型和操作系统配置，在x86处理器上多为2GB
    printf("Total space of virtual memory : %.2f GB \n",
           (float)memoryStatus.ullTotalVirtual/Gsize);
    //当前调用进程的虚拟地址空间的用户模式中未保留和未提交的内存量（单位：字节）
    printf("Avail space of virtual memory : %.2f GB \n",
           (float)memoryStatus.ullAvailVirtual/Gsize);
    printf("\n");
}

void getSystemInfo(){
    SYSTEM_INFO si;
    ZeroMemory(&si,sizeof(si));
    GetSystemInfo(&si);
    //页面大小和页面保护和提交的粒度，是VirtualAlloc函数使用的页面大小
    printf("The page size and the granularity of page protection and commitment is %dKB\n",
           (int)si.dwPageSize/Ksize);
    //指向应用程序和动态链接库（DLL）可访问的最低内存指针
    printf("The pointer to the lowest memory address accessible to applications and DLLs is 0x%.8x\n",
           si.lpMinimumApplicationAddress);
    //指向应用程序和动态链接库（DLL）可访问的最高内存指针
    printf("The pointer to the highest memory address accessible to applications and DLLs is 0x%.8x \n",
           si.lpMaximumApplicationAddress);
    //可以分配虚拟内存的起始地址的粒度
    printf("The granularity for the starting address at which virtual memory can be allocated is %d KB\n",
           si.dwAllocationGranularity/Ksize);
    printf("\n");
}

void getPerformanceInfo(){
    PERFORMANCE_INFORMATION pi;
    pi.cb=sizeof(pi);//结构体大小，需要初始化
    GetPerformanceInfo(&pi, sizeof(pi));
    //系统当前提交的页数，提交页面（使用VirtualAlloc和MEM_COMMIT）会立即更新该值；但是在访问页面之前，物理内存不会被填充
    printf("The number of pages currently committed by the system is %d\n",
           pi.CommitTotal);
    //自上次系统重新引导以来同时处于已提交状态的最大页数
    printf("The maximum number of pages that were simultaneously in the committed state since the last system reboot is %d\n",
           pi.CommitPeak);
    //实际物理内存，以页为单位
    printf("The amount of actual physical memory in pages is %d\n",
           pi.PhysicalTotal);
    //当前可用的物理内存量，以页为单位。这部分内存是可以立即重用无需写入磁盘的内存，是备用，空闲和零列表大小的总和
    printf("The amount of physical memory currently available is %d\n",
           pi.PhysicalAvailable);
    //系统缓存内存量，以页为单位。该值为备用列表大小加上系统工作集
    printf("The amount of system cache memory is %d\n",
           pi.SystemCache);
    //分页和非分页内核池中当前内存的总和，以页为单位
    printf("The sum of the memory currently in the paged and nonpaged kernel pools is %d\n",
           pi.KernelTotal);
    //当前在分页内核池的内存，以页为单位
    printf("The memory currently in the paged kernel pool is %d\n",
           pi.KernelPaged);
    //当前在非分页内核池中的内存，以页为单位
    printf("The memory currently in the nonpaged kernel pool is %d\n",
           pi.KernelNonpaged);
    //页面大小，以字节为单位
    printf("The size of a page is %dKB\n",
           pi.PageSize/Ksize);
    //当前打开句柄的数量
    printf("The current number of open handles is %d\n",
           pi.HandleCount);
    //当前进程数
    printf("The current number of processes is %d\n",
           pi.ProcessCount);
    //当前进程数
    printf("The current number of threads is %d\n",
           pi.ThreadCount);
    printf("\n\n");
}

void getProcessInfo()
{
    PROCESSENTRY32 pe;
    pe.dwSize=sizeof(pe);
    HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    BOOL bMore = ::Process32First(hProcessSnap, &pe);
    printf("PID\t | Execute File\t\t\t\t\t | Working Set Size(KB)\n");
    while(bMore){
        HANDLE hP = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe.th32ProcessID);
        PROCESS_MEMORY_COUNTERS pmc;
        ZeroMemory(&pmc, sizeof(pmc));
        if(GetProcessMemoryInfo(hP, &pmc, sizeof(pmc))){
            int len=strlen(pe.szExeFile);
            printf("%d\t | %s",pe.th32ProcessID,pe.szExeFile);
            for(int i=0;i<=45-len;i++){
                printf(" ");//控制长度，打表好看
            }
            printf("| %.2f\n",(float)pmc.WorkingSetSize/Ksize);
        }
        bMore = ::Process32Next(hProcessSnap, &pe);
    }
    CloseHandle(hProcessSnap);
    printf("\n\n");
}

//显示保护标记,该标记表示允许应用程序对内存进行访问的类型,参考课本292页
inline bool TestSet(DWORD dwTarget, DWORD dwMask)
{
    return ((dwTarget & dwMask) == dwMask);
}

#define SHOWMASK(dwTarget, type)        \
	if (TestSet(dwTarget, PAGE_##type)) \
	{                                   \
		cout << "," << #type;           \
	}

//显示当前块页面保护方式
void ShowProtection(DWORD dwTarget)
{
    //定义的页面保护方式
    SHOWMASK(dwTarget, READONLY);		   //只读
    SHOWMASK(dwTarget, GUARD);			   //保护
    SHOWMASK(dwTarget, NOCACHE);		   //无缓存
    SHOWMASK(dwTarget, READWRITE);		   //读写
    SHOWMASK(dwTarget, WRITECOPY);		   //写时复制
    SHOWMASK(dwTarget, EXECUTE);		   //执行
    SHOWMASK(dwTarget, EXECUTE_READ);	   //执行读
    SHOWMASK(dwTarget, EXECUTE_READWRITE); //执行读写
    SHOWMASK(dwTarget, EXECUTE_WRITECOPY); //执行写时复制
    SHOWMASK(dwTarget, NOACCESS);		   //未访问
}

//获取某一进程的虚拟地址空间布局和工作集信息
void ShowVirtualMemoryInfoAndWorkingSetInfo()
{
    int pid;
    cout << "pleaze enter query PID(enter -1 to return):";
    cin >> pid;
    if (pid == -1){
        printf("\n\n");
        return;
    }
    HANDLE hProcess;
    while (true) //判断输入的PID是否正确
    {
        hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
        if (hProcess == nullptr)
            cout << "wrong pid,please enter again(enter -1 to return):";
        else
            break;
        cin >> pid;
        if (pid == -1)
        {
            cout << endl
                 << endl;
            return;
        }
    }
    cout <<"process pid["<< pid << "] VirtualMemory && WorkingSet Info:" << endl
         << endl;
    SYSTEM_INFO si;
    ZeroMemory(&si, sizeof(si));
    GetSystemInfo(&si);
    MEMORY_BASIC_INFORMATION mbi;  //进程虚拟内存空间的基本信息结构
    ZeroMemory(&mbi, sizeof(mbi)); //分配缓冲区,用于保存信息

    auto pBlock = (LPCVOID)si.lpMinimumApplicationAddress;
    //遍历整个程序的地址空间
    for (; pBlock < si.lpMaximumApplicationAddress;)
    {
        if (VirtualQueryEx(hProcess,					//相关的进程
                           pBlock,										//开始位置
                           &mbi,										//缓冲区
                           sizeof(mbi)) == sizeof(mbi))				//长度的确认
            //查询地址空间中内存地址的信息
        {
            //计算块的结尾及其长度
            LPCVOID pEnd = (PBYTE)pBlock + mbi.RegionSize; //页基地址+虚存区大小
            TCHAR szSize[MAX_PATH];
            StrFormatByteSize(mbi.RegionSize, szSize, MAX_PATH); //格式化文件的大小
            //显示块地址和长度
            printf("address: %8X-%8X(%s)     ", pBlock, pEnd, szSize);
            int l = lstrlen(szSize);
            int x = 10 - l;
            for (int i = 0; i < x; i++) //对齐格式
                printf(" ");
            //显示块的状态
            if (mbi.State == MEM_COMMIT)
                cout << "comitted";
            else if (mbi.State == MEM_FREE)
                cout << "free";
            else if (mbi.State == MEM_RESERVE)
                cout << "reserved";
            //显示保护
            if (mbi.Protect == 0 && mbi.State != MEM_FREE)
                mbi.Protect = PAGE_READONLY;
            ShowProtection(mbi.Protect);
            //显示类型
            if (mbi.Type == MEM_IMAGE)
                cout << ",Image";
            else if (mbi.Type == MEM_PRIVATE)
                cout << ",Private";
            else if (mbi.Type == MEM_MAPPED)
                cout << ",Mapped";
            //检验可执行的映像
            TCHAR szFilename[MAX_PATH];				//提取用于当前可执行文件的文件名
            if (GetModuleFileName((HMODULE)pBlock,	//实际虚拟内存的模块句柄
                                  szFilename,							//完全指定的文件名称
                                  MAX_PATH) > 0)						//实际使用的缓冲区长度
            {
                PathStripPath(szFilename); //除去路径
                cout << ",Module:" << szFilename;
            }
            cout << endl;
            pBlock = pEnd; //移动指针以获得下一个块
        }
    }
    PROCESS_MEMORY_COUNTERS p;
    ZeroMemory(&p, sizeof(p));
    GetProcessMemoryInfo(hProcess, &p, sizeof(p));
    cout << endl
         << "WorkingSet Size:" << (float)p.WorkingSetSize / 1024 << "KB" << endl;
    printf("\n\n");
}

int main(){
    char mode;
    while(true){
        printf("==============================================\n");
        printf("functions provided are as followed.\n");
        printf("[m]:Memory Status\n");
        printf("[s]:System Info\n");
        printf("[p]:Performance Info\n");
        printf("[o]:Process Info\n");
        printf("[v]:VirtualMemory&&WorkingSet Info\n");
        printf("[q]:quit\n");
        printf("enter your choice:");
        mode = (char)getchar();
        getchar();
        printf("\n");
        switch(mode){
            case 'm':
                getMemoryInfo();//获取内存状态
                break;
            case 's':
                getSystemInfo();//获取性能信息
                break;
            case 'p':
                getPerformanceInfo();//获取性能信息
                break;
            case 'o':
                getProcessInfo();//打印当前进程列表
                break;
            case 'v':
                ShowVirtualMemoryInfoAndWorkingSetInfo();
                break;
            case 'q':
                return 0;
            default:
                continue;
        }
    }
}