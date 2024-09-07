#include "StateMachine.h"

namespace System {
	void StateMachine::add_state(state_ref new_state, bool _is_replacing) {
		this->is_adding = true;
		this->is_replacing = _is_replacing;

		this->new_state = std::move(new_state);
	}

	void StateMachine::remove_state() {
		this->is_removing = true;
	}

	void StateMachine::process_state_changes() {
		if (this->is_removing && !this->states.empty()) {
			this->states.pop();
			if (!this->states.empty()) {
				this->states.top()->Resume();
			}
			this->is_removing = false;
		}

		if (this->is_adding) {
			if (!this->states.empty()) {
				if (this->is_replacing) {
					this->states.pop();
				}
				else {
					this->states.top()->Pause();
				}
			}
			this->states.push(std::move(this->new_state));
			this->states.top()->Init();
			this->is_adding = false;

		}
	}

	state_ref& StateMachine::get_active_state() {
		return this->states.top();
	}
}