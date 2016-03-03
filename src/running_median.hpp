/*
* This may not actually be 'running median'. The object stores ALL values and computes
* median EXACTLY. Maybe it's a 'streaming median', I don't know...
*/
#ifndef RUNNING_MEDIAN_HPP
#define RUNNING_MEDIAN_HPP

#include <queue>

template <class T> class RunningMedian
{
public:
    void Push(const T &value) {
        size_t sizeSum = m_minHeap.size() + m_maxHeap.size();
        if (sizeSum == 0) {
            m_minHeap.push(value);
            return;
        }

        if (sizeSum == 1) {
            m_minHeap.push(value);
            m_maxHeap.push(m_minHeap.top());
            m_minHeap.pop();
            return;
        }

        if (value < m_maxHeap.top()) {
            m_maxHeap.push(value);
            if (m_maxHeap.size() > m_minHeap.size()) {
                m_minHeap.push(m_maxHeap.top());
                m_maxHeap.pop();
            }
        } else {
            m_minHeap.push(value);
            if (m_minHeap.size() > m_maxHeap.size()) {
                m_maxHeap.push(m_minHeap.top());
                m_minHeap.pop();
            }
        }
    }

    T Median() {
        T res;
        if (m_minHeap.size() > m_maxHeap.size()) {
            res = m_minHeap.top();
        } else if (m_maxHeap.size() > m_minHeap.size()) {
            res = m_maxHeap.top();
        } else {
            res = (m_minHeap.top() + m_maxHeap.top()) / 2;
        }
        return res;
    }

private:
    std::priority_queue<T> m_minHeap, m_maxHeap;
};

#endif
