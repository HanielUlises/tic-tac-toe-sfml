#pragma once

#include <memory>
#include <stack>

#include "State.h"

namespace System {
	// Renaming the smart pointer with a typedef
	typedef std::unique_ptr<State> state_ref;

	class StateMachine {
	public:
		StateMachine() {}
		~StateMachine() {}
		
		void add_state(state_ref newState, bool is_replacing = true);
		void remove_state();

		void process_state_changes();

		state_ref& get_active_state();
		
	private:
		std::stack<state_ref> states;
		state_ref new_state;

		bool is_removing;
		bool is_adding;
		bool is_replacing;
	};
}
