#pragma once

namespace System {
	class State {
	public:
		virtual void Init() = 0;
		virtual void HandleInput() = 0;
		virtual void Update(float delta) = 0;
		virtual void Draw(float delta) = 0;

		virtual void Pause() {}
		virtual void Resume() {}
	};
}