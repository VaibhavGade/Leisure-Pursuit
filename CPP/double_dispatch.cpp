namespace double_dispatch
{
	class A;
	class A1;
	class A2;
	class B1;
	class B2;

	class B {
	public:
		// dispatcher function to A
		virtual void collide(const A& a) const = 0;

		// actual collision logic B with types of A
		virtual void collide(const A1& a) const = 0;
		virtual void collide(const A2& a) const = 0;
	};

	class A {
	public:
		// dispatcher function to B
		virtual void collide(const B& b) const = 0;

		// actual collision logic A with types of B
		virtual void collide(const B1& b) const = 0;
		virtual void collide(const B2& b) const = 0;
	};

	class A1 : public A {
	public:
		void collide(const B& b) const {
			// dispatch to b
			b.collide(*this);
		}
		void collide(const B1& b) const {
			cout << "collision with B1 and A1" << endl;
		}
		void collide(const B2& b) const {
			cout << "collision with B2 and A1" << endl;
		}
	};

	class A2 : public A {
	public:
		void collide(const B& b) const {
			// dispatch to a
			b.collide(*this);
		}
		void collide(const B1& b) const {
			cout << "collision with B1 and A2" << endl;
		}
		void collide(const B2& b) const {
			cout << "collision with B2 and A2" << endl;
		}
	};

	class B1 : public B {
	public:
		void collide(const A& b) const {
			b.collide(*this);
		}
		void collide(const A1& b) const {
			cout << "collision with A1 Bnd B1" << endl;
		}
		void collide(const A2& b) const {
			cout << "collision with A2 Bnd B1" << endl;
		}
	};

	class B2 : public B {
	public:
		void collide(const A& a) const {
			a.collide(*this);
		}
		void collide(const A1& a) const {
			cout << "collision with A1 Bnd B2" << endl;
		}
		void collide(const A2& a) const {
			cout << "collision with A2 Bnd B2" << endl;
		}
	};
}

void entry_point()
{
	//https://stackoverflow.com/questions/12582040/understanding-double-dispatch-c
	double_dispatch::A *pA = new double_dispatch::A1;
	double_dispatch::B *pB = new double_dispatch::B2;

	pA->collide(*pB);
}
