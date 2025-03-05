#include "pch.h"
#include "CReportCard.h"

CReportCard::CReportCard()
{
    m_pStudent = nullptr;
    vecStudent.reserve(30);
}

CReportCard::~CReportCard()
{
    Release();
}

void CReportCard::Initialize()
{
    if(nullptr == m_pStudent)
        m_pStudent = new CStudent;
}

void CReportCard::Update()
{
    int iInput(0);
    

    while (true)
    {
        SYSTEM_CLOSE;
        cout << "-------------------성적표 프로그램------------------" << endl;
        cout << "1. 성적 입력 2. 성적 출력 3. 검색 4. 삭제 5. 정렬 6. 종료 \n >> ";
        cin >> iInput;

        switch (iInput)
        {
        case 1:
            Input();
            SYSTEM_PAUSE;
            break;

        case 2:
            Print();
            SYSTEM_PAUSE;
            break;

        case 3:
            Search();
            SYSTEM_PAUSE;
            break;

        case 4:
            Delete();
            SYSTEM_PAUSE;
            break;

        case 5:
            Sort();
            SYSTEM_PAUSE;
            break;

        case 6:
            cout << "프로그램 종료";
            return;
        default:
            break;
        }
    }
}

void CReportCard::Release()
{
    vector<CStudent*>::iterator iter;
    for (iter = vecStudent.begin(); iter != vecStudent.end();++iter)
    {
        Safe_Delete(*iter);
    }
}

void CReportCard::Input()
{
    m_pStudent = new CStudent;
    INFO tTmp;
    cout << "학생의 이름을 입력하세요 >> ";
    cin >> tTmp.sName;
    cout << "학생의 국어 점수를 입력하세요 >>  ";
    cin >> tTmp.iKorean;
    cout << "학생의 영어 점수를 입력하세요 >> ";
    cin >> tTmp.iEnglish;
    cout << "학생의 수학 점수를 입력하세요 >> ";
    cin >> tTmp.iMath;
    m_pStudent->Set_Info(tTmp.sName, tTmp.iKorean, tTmp.iEnglish, tTmp.iMath);
    vecStudent.push_back(m_pStudent);
}

void CReportCard::Print()
{
    if(0 < vecStudent.size())
    {
        vector<CStudent*>::iterator iter;
        for (iter = vecStudent.begin(); iter != vecStudent.end(); ++iter)
        {
            cout << "---------------------------------------------" << endl;
            cout << "이름 : " << (*iter)->Get_Name() << endl;
            cout << "국어 점수 : " << (*iter)->Get_Korean() << endl;
            cout << "영어 점수 : " << (*iter)->Get_English() << endl;
            cout << "수학 점수 : " << (*iter)->Get_Math() << endl;
            cout << "총합 : " << (*iter)->Get_Total() << endl;
            cout << "평균 : " << (*iter)->Get_Average() << endl;

        }
    }
    else
        cout << "학생 정보가 없습니다." << endl;
}

void CReportCard::Search()
{
    if (0 < vecStudent.size())
    {
        bool bSearch = false;
        string sName;
        cout << " 검색할 학생의 이름을 입력하세요 >> ";
        cin >> sName;
        vector<CStudent*>::iterator iter;
        for (iter = vecStudent.begin(); iter != vecStudent.end(); ++iter)
        {
            if (sName == (*iter)->Get_Name())
            {
                bSearch = true;
                cout << "---------------------------------------------" << endl;
                cout << "이름 : " << (*iter)->Get_Name() << endl;
                cout << "국어 점수 : " << (*iter)->Get_Name() << endl;
                cout << "영어 점수 : " << (*iter)->Get_Name() << endl;
                cout << "수학 점수 : " << (*iter)->Get_Name() << endl;
                cout << "총합 : " << (*iter)->Get_Name() << endl;
                cout << "평균 : " << (*iter)->Get_Name() << endl;
                cout << "---------------------------------------------" << endl;
            }
        }
        if(!bSearch)
            cout << "없는 학생입니다." << endl;
    }
    else
        cout << "학생 정보가 없습니다." << endl;
}

void CReportCard::Delete()
{
    
    if (0 < vecStudent.size())
    {
        bool bDelete = false;
        string sName;
        cout << " 삭제할 학생의 이름을 입력하세요 >> ";
        cin >> sName;
        
        vector<CStudent*>::iterator iter;
        for (iter = vecStudent.begin(); iter != vecStudent.end();)
        {
            if (sName == (*iter)->Get_Name())
            {
                bDelete = true;

                cout << "---------------------------------------------" << endl;
                cout << (*iter)->Get_Name() << " 학생의 정보를 삭제하였습니다." << endl;
                cout << "---------------------------------------------" << endl;
                Safe_Delete(*iter);
                iter = vecStudent.erase(iter);
            }
            else
                ++iter;
        }
        if (!bDelete)
            cout << "없는 학생입니다." << endl;
    }
    else
        cout << "학생 정보가 없습니다." << endl;
}

void CReportCard::Sort()
{
   sort(vecStudent.begin(), vecStudent.end());
}

