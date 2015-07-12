/***************************************************************************
Copyright Dec/2010
MUSiiC Laboratory
Hyun-Jae Kang, Emad M Boctor
Johns Hopkins Medical Institutions
Department of Radiology, Division of Medical Imaging Physics

For commercial use/licensing, please contact Emad Boctor, Ph.D. at eboctor@jhmi.edu.

***************************************************************************/

#include "MUSiiCigtlMsgVector.h"

namespace igtl
{
	MUSiiCigtlMsgVector::MUSiiCigtlMsgVector()
	{
		m_Cond	= igtl::ConditionVariable::New();
	}
	
	MUSiiCigtlMsgVector::~MUSiiCigtlMsgVector()
	{

	}
	
	/// Find an index of specific igtlMessage on MUSiiCVector
	int MUSiiCigtlMsgVector::Find_igtlMsg(igtl::MessageBase::Pointer data, std::vector<int>& list)
	{
		int start,sz, cnt;
		//list.clear();
		
		cnt = 0;
		sz = size();
		
		if( strcmp(data->GetDeviceType(), "") == 0		||
			strcmp(data->GetDeviceType(), "ALL") == 0	||
			strcmp(data->GetDeviceType(), "All") == 0	||
			strcmp(data->GetDeviceType(), "all") == 0)
		{
			list.clear();
			for(int i=0; i<sz;i++)
				list.push_back(i);
			cnt = sz;
		}
		else
		{
			if(list.empty())
				start = 0;
			else
			{
				int ssz = list.size();
				start = list[ssz-1] + 1;
			}
		
			for(int i=start; i<sz; i++)
			{
				if(strcmp(data->GetDeviceType(), m_MVector[i]->GetDeviceType()) == 0 )
				{
					list.push_back(i);
					cnt++;
				}
			}
		}
		
		return cnt;
	}
	
	/// Get the number of a specific igtlMessage on MUSiiCVector
	int MUSiiCigtlMsgVector::GetCount_igtlMsg(igtl::MessageBase::Pointer data)
	{
		int sz;
		int cnt = 0;
		sz = size();
		
		for(int i=0; i<sz; i++)
		{
			if(strcmp(data->GetDeviceType(), m_MVector[i]->GetDeviceType()) == 0 )
				cnt++;
		}
		
		return cnt;
	}
	
	/// Get idx-th element (a specific igtlMessage) from vector without removing the element
	/// the idx is zero-base
	/// Without Condition variable (without waiting)
	int MUSiiCigtlMsgVector::concurrent_try_get(igtl::MessageBase::Pointer data, int idx)
	{
		int s, local_idx;
		std::vector<int> list;
		list.clear();
		/// Lock the mutex
		m_Lock.Lock();
		//Find specific igtlMessages on vector
		//s = Find_igtlMsg(data, list);
		/// Get size of vector
		/*s = list.size();
		/// check whether vector is empty or not
		if(m_MVector.empty() || idx < 0 || idx >= s || s<=0)
		{
			m_Lock.Unlock();
			return -1;
		}
		local_idx = list[idx];*/
		/// Get the first element from vector
		data = m_MVector[idx];
		/// Release mutex
		m_Lock.Unlock();
		/// return the size of vector 
		return s;	
	}
	
	/// Get idx-th element (a specific igtlMessage) from vector with removing the element
	/// the idx is zero-base
	/// Without Condition variable (without waiting)
	int MUSiiCigtlMsgVector::concurrent_try_get_pop(igtl::MessageBase::Pointer data, int idx, bool dropping)
	{
		int s, local_idx;
		std::vector<int> list;
		list.clear();
		/// Lock the mutex
		m_Lock.Lock();
		//Find specific igtlMessages on vector
		s = Find_igtlMsg(data, list);
		/// Get size of vector
		s = list.size();
		/// check whether vector is empty or not
		if(m_MVector.empty() || idx < 0 || idx >= s || s<=0)
		{
			m_Lock.Unlock();
			return -1;
		}
		local_idx = list[idx];
		/// Get the first element from vector
		data = m_MVector[local_idx];
		/// Delete the first element of vector
		erase_element(local_idx);
		
		/// Dropping 
		if(dropping)
		{
			list.erase(list.begin()+idx, list.end());
			drop_elements(list);
			s = list.size();
		}
		else
			s = s-1;
		
		/// Release mutex
		m_Lock.Unlock();
		/// return the size of vector 
		return s;
	}
	
	/// Get the first element (a specific igtlMessage) from vector without removing the element
	/// Without Condition variable (waiting)
	int MUSiiCigtlMsgVector::concurrent_try_get_front(igtl::MessageBase::Pointer data)
	{
		return concurrent_try_get_pop(data, 0);
	}
	
	/// Get the first element (a specific igtlMessage)from vector with removing the element
	/// Without Condition variable (waiting)
	int MUSiiCigtlMsgVector::concurrent_try_get_pop_front(igtl::MessageBase::Pointer data)
	{
		return concurrent_try_get_pop(data, 0, false);
	}
	
	/// Get the last element from vector without removing the element
	/// Without Condition variable (waiting)
	int MUSiiCigtlMsgVector::concurrent_try_get_back(igtl::MessageBase::Pointer data)
	{
		int s, local_idx;
		std::vector<int> list;
		list.clear();
		/// Lock the mutex
		m_Lock.Lock();
		//Find specific igtlMessages on vector
		s = Find_igtlMsg(data, list);
		/// Get size of vector
		s = list.size();
		/// check whether vector is empty or not
		if(m_MVector.empty() || s<=0)
		{
			m_Lock.Unlock();
			return -1;
		}
		local_idx = list[s-1];
		/// Get the first element from vector
		data = m_MVector[local_idx];
		/// Release mutex
		m_Lock.Unlock();
		/// return the size of vector 
		return s;
	}
	
	/// Get the last element from vector with removing the element
	/// Without Condition variable (waiting)
	int MUSiiCigtlMsgVector::concurrent_try_get_pop_back(igtl::MessageBase::Pointer data, bool dropping)
	{
		int s, local_idx;
		std::vector<int> list;
		list.clear();
		/// Lock the mutex
		m_Lock.Lock();
		//Find specific igtlMessages on vector
		s = Find_igtlMsg(data, list);
		/// Get size of vector
		s = list.size();
		/// check whether vector is empty or not
		if(m_MVector.empty() || s<=0)
		{
			m_Lock.Unlock();
			return -1;
		}
		local_idx = list[s-1];
		/// Get the first element from vector
		data = m_MVector[local_idx];
		/// Delete the first element of vector
		erase_element(local_idx);
		
		/// Dropping 
		if(dropping)
		{
			list.pop_back();
			drop_elements(list);
			s = 0;
		}
		else
			s = s-1;
			
		/// Release mutex
		m_Lock.Unlock();
		/// return the size of vector 
		return s-1;
	}
	
	/// Get idx-th element (a specific igtlMessage) from vector without removing the element
	/// the idx is zero-base 
	/// With Condition variable
	int MUSiiCigtlMsgVector::concurrent_wait_get(igtl::MessageBase::Pointer data, int idx)
	{
		if(idx < 0 ) return -1;
		int s, local_idx;
		std::vector<int> list;
		list.clear();
		while(1)
		{
			m_Lock.Lock();
			s = Find_igtlMsg(data, list);
			
			if(!m_MVector.empty() && idx < s)
			{
				break;
			}
			else if(m_MVector.empty() && idx >= s &&m_bTerminate)
			{
				m_bTerminate = false;
				m_bWaiting = false;
				m_Lock.Unlock();
				return -1;
			}
			else
			{
				m_bWaiting	= true;
				m_Lock.Unlock();
				m_Cond->Wait(&m_Lock);
				continue;
			}
		}
		
		local_idx = list[idx];
		data = m_MVector[local_idx];
		m_Lock.Unlock();
		return s;
	}
	
	/// Get idx-th element (a specific igtlMessage) from vector with removing the element
	/// the idx is zero-base 
	/// With Condition variable
	int MUSiiCigtlMsgVector::concurrent_wait_get_pop(igtl::MessageBase::Pointer data, int idx, bool dropping)
	{
		if(idx < 0 ) return -1;
		int s, local_idx;
		std::vector<int> list;
		list.clear();
		while(1)
		{
			m_Lock.Lock();
			s = Find_igtlMsg(data, list);
			
			if(!m_MVector.empty() && idx < s)
			{
				break;
			}
			else if(m_MVector.empty() && idx >= s &&m_bTerminate)
			{
				m_bTerminate = false;
				m_bWaiting = false;
				m_Lock.Unlock();
				return -1;
			}
			else
			{
				m_bWaiting	= true;
				m_Lock.Unlock();
				m_Cond->Wait(&m_Lock);
				continue;
			}
		}
		
		local_idx = list[idx];
		data = m_MVector[local_idx];
		erase_element(local_idx);
		
		///Dropping
		if(dropping)
		{
			list.erase(list.begin()+idx, list.end());
			drop_elements(list);
			s = list.size();
		}
		else
			s = s-1;
		
		m_Lock.Unlock();
		return s;
	}
	
	
	/// Get the first element (a specific igtlMessage) from vector without removing the element
	/// With Condition variable (waiting)
	int MUSiiCigtlMsgVector::concurrent_wait_get_front(igtl::MessageBase::Pointer data)
	{
		return concurrent_wait_get(data, 0);
	}
	
	/// Get the first element (a specific igtlMessage) from vector with removing the element
	/// With Condition variable (waiting)
	int MUSiiCigtlMsgVector::concurrent_wait_get_pop_front(igtl::MessageBase::Pointer data)
	{
		return concurrent_wait_get_pop(data, 0, false);
	}
	
	/// Get the first element (a specific igtlMessage) from vector without removing the element
	/// With Condition variable (waiting)
	int MUSiiCigtlMsgVector::concurrent_wait_get_back(igtl::MessageBase::Pointer data)
	{
			
		int s, local_idx;
		std::vector<int> list;
		list.clear();
		
		while(1)
		{
			m_Lock.Lock();
			s = Find_igtlMsg(data, list);
			
			if(!m_MVector.empty() && s > 0)
			{
				break;
			}
			else if(m_MVector.empty() && s <= 0 &&m_bTerminate)
			{
				m_bTerminate = false;
				m_bWaiting = false;
				m_Lock.Unlock();
				return -1;
			}
			else
			{
				m_bWaiting	= true;
				m_Lock.Unlock();
				m_Cond->Wait(&m_Lock);
				continue;
			}
		}
		
		local_idx = list[s-1];
		data = m_MVector[local_idx];
		m_Lock.Unlock();
		return s;
	}
	
	/// Get the first element (a specific igtlMessage) from vector with removing the element
	/// With Condition variable (waiting)
	int MUSiiCigtlMsgVector::concurrent_wait_get_pop_back(igtl::MessageBase::Pointer data, bool dropping)
	{
		int s, local_idx;
		std::vector<int> list;
		list.clear();
		while(1)
		{
			m_Lock.Lock();
			s = Find_igtlMsg(data, list);
			
			if(!m_MVector.empty() && s > 0)
			{
				break;
			}
			else if(m_MVector.empty() && s <= 0 &&m_bTerminate)
			{
				m_bTerminate = false;
				m_bWaiting = false;
				m_Lock.Unlock();
				return -1;
			}
			else
			{
				m_bWaiting	= true;
				m_Lock.Unlock();
				m_Cond->Wait(&m_Lock);
				continue;
			}
		}
		
		local_idx = list[s-1];
		data = m_MVector[local_idx];
		erase_element(local_idx);
		
		///Dropping
		if(dropping)
		{
			list.pop_back();
			drop_elements(list);
			s = 0;
		}
		else
			s = s-1;
		
		m_Lock.Unlock();
		return s;
	}
	
	
	
}