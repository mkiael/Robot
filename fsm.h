/*

#ifndef FSM_H_
#define FSM_H_

enum Signal
{
	ENTRY_SIGNAL = 0,
	EXIT_SIGNAL,
	USER_SIGNAL = 1000
};

class Event
{
public:

	Event(Signal signal);

	Signal getSignal() const;

private:

	Signal m_signal;

};

template<class FsmT>
class Fsm
{
public:

	typedef int (FsmT::*State)(Event const* e);

	Fsm(State initialState);

	void dispatch(Event const* e);

private:

	void transition(State nextState);

	State m_currentState;

	Event m_evEntry;

	Event m_evExit;

};

template<class FsmT>
inline Fsm<FsmT>::Fsm(State initialState)
: m_currentState(initialState)
, m_evEntry(ENTRY_SIGNAL)
, m_evExit(EXIT_SIGNAL)
{
}

template<class FsmT>
inline void Fsm<FsmT>::dispatch(Event const* e)
{
	m_currentState(e);
}

template<class FsmT>
inline void Fsm<FsmT>::transition(State nextState)
{
	m_currentState(&m_evExit);
	m_currentState = nextState;
	m_currentState(&m_evEntry);
}
#endif /* FSM_H_ */

*/
