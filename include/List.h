//
//  List.h
//  mp2-lab5-list
//
//  Created by Андрей Лебедев on 21.02.2020.
//  Copyright © 2020 Андрей Лебедев. All rights reserved.
//

#pragma once
#include <iostream>
#include <math.h>
using namespace std;

struct TMonom{
    double coeff;
    int px, py, pz;
    TMonom(){
        coeff = 0;
        px = py = pz =0;
    }
    bool operator ==(TMonom m){
        return px == m.px && py == m.py && pz == m.pz;
    }
    
    bool operator >(TMonom m){
        if (px != m.px){
            return px > m.px;
        } else if (py != m.py){
            return py > m.py;
        } else return pz > m.pz;
    }
    
    bool operator <(TMonom m){
           if (px != m.px){
               return px < m.px;
           } else if (py != m.py){
               return py < m.py;
           } else return pz < m.pz;
       }
    
    TMonom operator+ (TMonom mon) {
        TMonom res = *this;
        res.coeff += mon.coeff;
        return res;
    }
    
    TMonom& operator+= (TMonom mon) {
           coeff += mon.coeff;
           return (*this);
       }
    
    friend ostream& operator<< (ostream& os, const TMonom& mon) {
        if (mon.coeff != 0) {
            if (mon.px == mon.py && mon.py == mon.pz && mon.pz == 0)
                os << " " << mon.coeff;
            else
                os << " " << mon.coeff << "x^" << mon.px << " y^" << mon.py << " z^" << mon.pz;
        }
        return os;
    }
};


template <class T>
struct TNode {
    T val;
    TNode<T>* pNext;
};

template <class T>
class TList{
protected:
    int pos, len;
    TNode<T> *pFirst, *pLast, *pCurr, *pPrev, *pStop;
public:
    TList(){
        pFirst = 0;
        pLast = 0;
        pCurr = 0;
        pPrev = 0;
        pStop = 0;
        len = 0;
        pos = -1;
    }
    
    ~TList(){
        DelList();
    }
    
    void DelList(){
        int size = len;
        for (int i = 0; i < size; i++)
        DelFirst();
    }
    
    void InsFirst(T el) {
        TNode<T>* tmp = new TNode<T>;
        tmp->pNext = pFirst;
        tmp->val = el;
        pFirst = tmp;
        if (pLast == pStop) pLast = tmp;
        len++;
        pos++;
    }
    
    void InsLast(T el) {
        if (pLast != pStop){
            TNode<T>* tmp = new TNode<T>;
            pLast->pNext = tmp;
            tmp->pNext = pStop;
            tmp->val = el;
            pLast = tmp;
            len++;
        } else {
            InsFirst(el);
        }
    }
    
    void InsCurr(T el) {
        TNode<T>* tmp = new TNode<T>;
        tmp->val = el;
        if (pCurr == pFirst) InsFirst(el);
        else {
            pPrev->pNext = tmp;
            tmp->pNext = pCurr;
            len++;
            pCurr = tmp;
        }
    }
    
    void DelFirst() {
		if (pCurr == pFirst) GoNext();
        TNode<T>* tmp;
        tmp = pFirst->pNext;
        delete pFirst;
        pFirst = tmp;
        len--;
        pos--;
    }
    
    void DelCurr(){
        if (pCurr == pFirst)
            DelFirst();
        else{
			pCurr = pCurr->pNext;
			delete pPrev->pNext;
			pPrev->pNext = pCurr;
            len--;
        }
    }
    
    T GetCurr() {
        return pCurr->val;
    }
    
    int GetLen() {
        return len;
    }
    
    void Reset() {
        pCurr = pFirst;
        pPrev = NULL;
        pos = 0;
    }
    
    void GoNext() {
        pPrev = pCurr;
        pCurr = pCurr->pNext;
        pos++;
    }
    
    bool IsEnd() {
        return pCurr == pStop;
    }
    
    bool IsEmpty() {
        return pFirst == pStop;
    }
    
    void InsOrder(T el) {
        if (pFirst == 0 || pFirst->val < el)
            InsFirst(el);
        else
            if (el <= pLast->val)
                InsLast(el);
            else
                for (Reset(); !IsEnd(); GoNext())
                    if (pCurr->val < el) {
                        InsCurr(el);
                        break;
                    }
    }
};

template <class T>
class HeadList: public TList<T>{
protected:
    TNode<T>* pHead;
public:
    HeadList(): TList<T>(){
        pHead = new TNode<T>;
        TList<T>::pStop = pHead;
        pHead->pNext = pHead;
        TList<T>::pFirst = pHead;
		TList<T>::pLast = pHead;
    }
    
    ~HeadList(){
       TList<T>::DelList();
	   delete pHead;
    }
    
    void InsFirst(T el){
        TList<T>::InsFirst(el);
        pHead->pNext = TList<T>::pFirst;
    }
    
    void DelFirst(){
        TList<T>::DelFirst();
        pHead->pNest = TList<T>::pFirst;
    }
    
};

class TPolynom: public HeadList<TMonom>{
public:
    
    TPolynom(): HeadList<TMonom>() {
        pHead->val.pz = -1;
    }
    
    TPolynom(int arr[][2], int size): HeadList<TMonom>() {
        pHead->val.pz = -1;
        for (int i = 0; i < size; i++) {
            TMonom mon;
            mon.coeff = arr[i][0];
            mon.px = arr[i][1] / 100;
            mon.py = arr[i][1] / 10 % 10;
            mon.pz = arr[i][1] % 10;
            InsLast(mon);
        }
    }
    
    TPolynom(TPolynom& pol): HeadList<TMonom>() {
        pHead->val.pz = -1;
        for (pol.Reset(); !pol.IsEnd(); pol.GoNext()) {
            TMonom mon = pol.pCurr->val;
            InsLast(mon);
        }
    }
    
    ~TPolynom(){
        DelList();
    }
    
    TPolynom& operator=(TPolynom& pol){
        DelList();
        for (pol.Reset(); !pol.IsEnd(); pol.GoNext()) {
            TMonom mon = pol.pCurr->val;
            InsLast(mon);
        }
        return (*this);
    }
    
    bool operator==(const TPolynom &pol) const{
        TNode<TMonom> *i1, *i2;
        i1 = pFirst;
        i2 = pol.pFirst;
        while (i1->val == i2->val && i1 != pStop && i2 != pStop) {
            i1 = i1->pNext;
            i2 = i2->pNext;
        }
        return (i1 == pStop) && (i2 == pol.pStop);
    }
    
    void operator+= (TMonom& mon){
        for (Reset(); !IsEnd(); GoNext()) {
            if (pCurr->val == mon) {
                pCurr->val += mon;
                if (!pCurr->val.coeff)
                    DelCurr();
                return;
            }
            if (mon > pCurr->val) {
                InsCurr(mon);
                return;
            }
        }
        InsLast(mon);
    }
    
    TPolynom operator+ (TMonom& mon){
        TPolynom res = *this;
        res += mon;
        return res;
    }
    
    void operator*= (TMonom& mon){
        for (Reset(); !IsEnd(); GoNext()) {
            pCurr->val.coeff *= mon.coeff;
            pCurr->val.px += mon.px;
            pCurr->val.py += mon.py;
            pCurr->val.pz += mon.pz;
        }
    }
    
    TPolynom operator* (TMonom& mon){
        TPolynom res = *this;
        res *= mon;
        return res;
    }
    
    void operator+= (TPolynom& q){
        TMonom pm, qm, rm;
        Reset();
        q.Reset();
        while (!q.IsEnd()) {
            pm = pCurr->val;
            qm = q.pCurr->val;
            if (pm > qm)
                GoNext();
            else
                if (pm < qm) {
                    InsCurr(qm);
                    q.GoNext();
                }
            else {
                rm = pm;
                rm.coeff += qm.coeff;
                pCurr->val = rm;
                if (rm.coeff == 0)
                    DelCurr();
				else
                GoNext();
                q.GoNext();
            }
        }
    }
    
    friend ostream& operator<< (ostream& os, TPolynom& pol) {
        os << pol.pFirst->val;
        for (pol.Reset(); !pol.IsEnd(); pol.GoNext()) {
            if (pol.pCurr == pol.pFirst) continue;
            if (pol.pCurr->val.coeff >= 0) os << " +";
            os << pol.pCurr->val;
        }
        os << endl;
        return os;
    }
};
