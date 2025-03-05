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
        cout << "-------------------����ǥ ���α׷�------------------" << endl;
        cout << "1. ���� �Է� 2. ���� ��� 3. �˻� 4. ���� 5. ���� 6. ���� \n >> ";
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
            cout << "���α׷� ����";
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
    cout << "�л��� �̸��� �Է��ϼ��� >> ";
    cin >> tTmp.sName;
    cout << "�л��� ���� ������ �Է��ϼ��� >>  ";
    cin >> tTmp.iKorean;
    cout << "�л��� ���� ������ �Է��ϼ��� >> ";
    cin >> tTmp.iEnglish;
    cout << "�л��� ���� ������ �Է��ϼ��� >> ";
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
            cout << "�̸� : " << (*iter)->Get_Name() << endl;
            cout << "���� ���� : " << (*iter)->Get_Korean() << endl;
            cout << "���� ���� : " << (*iter)->Get_English() << endl;
            cout << "���� ���� : " << (*iter)->Get_Math() << endl;
            cout << "���� : " << (*iter)->Get_Total() << endl;
            cout << "��� : " << (*iter)->Get_Average() << endl;

        }
    }
    else
        cout << "�л� ������ �����ϴ�." << endl;
}

void CReportCard::Search()
{
    if (0 < vecStudent.size())
    {
        bool bSearch = false;
        string sName;
        cout << " �˻��� �л��� �̸��� �Է��ϼ��� >> ";
        cin >> sName;
        vector<CStudent*>::iterator iter;
        for (iter = vecStudent.begin(); iter != vecStudent.end(); ++iter)
        {
            if (sName == (*iter)->Get_Name())
            {
                bSearch = true;
                cout << "---------------------------------------------" << endl;
                cout << "�̸� : " << (*iter)->Get_Name() << endl;
                cout << "���� ���� : " << (*iter)->Get_Name() << endl;
                cout << "���� ���� : " << (*iter)->Get_Name() << endl;
                cout << "���� ���� : " << (*iter)->Get_Name() << endl;
                cout << "���� : " << (*iter)->Get_Name() << endl;
                cout << "��� : " << (*iter)->Get_Name() << endl;
                cout << "---------------------------------------------" << endl;
            }
        }
        if(!bSearch)
            cout << "���� �л��Դϴ�." << endl;
    }
    else
        cout << "�л� ������ �����ϴ�." << endl;
}

void CReportCard::Delete()
{
    
    if (0 < vecStudent.size())
    {
        bool bDelete = false;
        string sName;
        cout << " ������ �л��� �̸��� �Է��ϼ��� >> ";
        cin >> sName;
        
        vector<CStudent*>::iterator iter;
        for (iter = vecStudent.begin(); iter != vecStudent.end();)
        {
            if (sName == (*iter)->Get_Name())
            {
                bDelete = true;

                cout << "---------------------------------------------" << endl;
                cout << (*iter)->Get_Name() << " �л��� ������ �����Ͽ����ϴ�." << endl;
                cout << "---------------------------------------------" << endl;
                Safe_Delete(*iter);
                iter = vecStudent.erase(iter);
            }
            else
                ++iter;
        }
        if (!bDelete)
            cout << "���� �л��Դϴ�." << endl;
    }
    else
        cout << "�л� ������ �����ϴ�." << endl;
}

void CReportCard::Sort()
{
   sort(vecStudent.begin(), vecStudent.end());
}

