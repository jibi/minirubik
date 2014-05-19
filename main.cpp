#include <iostream>
#include <cstring>
#include <queue>
#include <unordered_map>

#include <cstdio>
#include <cstdlib>
#include <ctime>

const char colors[6] = { 'w', 'r', 'b', 'g', 'o', 'y'};

typedef enum faces_e {
	FRONT,
	BACK,
	LEFT,
	RIGHT,
	TOP,
	BOTTOM
} faces_t;

class cube {
public:
	char faces[6][4];
	char depth;

	cube() {
		int i,j;

		for (i = 0; i < 6; i++) {
			for (j = 0; j < 4; j++) {
				faces[i][j] = (char) colors[i];
			}
		}

		depth = 0;
	}

	void
	rotate_front() {
		char t0, t1;

		t0               = faces[FRONT][0];
		faces[FRONT][0]  = faces[FRONT][3];
		faces[FRONT][3]  = faces[FRONT][2];
		faces[FRONT][2]  = faces[FRONT][1];
		faces[FRONT][1]  = t0;

		t0               = faces[TOP][2];
		t1               = faces[TOP][3];

		faces[TOP][2]    = faces[LEFT][1];
		faces[TOP][3]    = faces[LEFT][2];

		faces[LEFT][1]   = faces[BOTTOM][0];
		faces[LEFT][2]   = faces[BOTTOM][1];

		faces[BOTTOM][0] = faces[RIGHT][3];
		faces[BOTTOM][1] = faces[RIGHT][0];

		faces[RIGHT][0]  = t1;
		faces[RIGHT][3]  = t0;
	}

	void
	rotate_back() {
		char t0, t1;

		t0               = faces[FRONT][0];
		faces[FRONT][0]  = faces[FRONT][1];
		faces[FRONT][1]  = faces[FRONT][2];
		faces[FRONT][2]  = faces[FRONT][3];
		faces[FRONT][3]  = t0;

		t0               = faces[TOP][2];
		t1               = faces[TOP][3];

		faces[TOP][2]    = faces[RIGHT][3];
		faces[TOP][3]    = faces[RIGHT][0];

		faces[RIGHT][0]  = faces[BOTTOM][1];
		faces[RIGHT][3]  = faces[BOTTOM][0];

		faces[BOTTOM][1] = faces[LEFT][2];
		faces[BOTTOM][0] = faces[LEFT][1];

		faces[LEFT][1]   = t0;
		faces[LEFT][2]   = t1;

	}

	void
	rotate_left() {
		char t0, t1;

		t0               = faces[LEFT][0];
		faces[LEFT][0]   = faces[LEFT][3];
		faces[LEFT][3]   = faces[LEFT][2];
		faces[LEFT][2]   = faces[LEFT][1];
		faces[LEFT][1]   = t0;

		t0               = faces[TOP][0];
		t1               = faces[TOP][3];

		faces[TOP][0]    = faces[BACK][0];
		faces[TOP][3]    = faces[BACK][3];

		faces[BACK][0]   = faces[BOTTOM][0];
		faces[BACK][3]   = faces[BOTTOM][3];

		faces[BOTTOM][0] = faces[FRONT][0];
		faces[BOTTOM][3] = faces[FRONT][3];

		faces[FRONT][0]  = t0;
		faces[FRONT][3]  = t1;

	}

	void
	rotate_right() {
		char t0, t1;

		t0               = faces[LEFT][0];
		faces[LEFT][0]   = faces[LEFT][1];
		faces[LEFT][1]   = faces[LEFT][2];
		faces[LEFT][2]   = faces[LEFT][3];
		faces[LEFT][3]   = t0;

		t0               = faces[TOP][0];
		t1               = faces[TOP][3];

		faces[TOP][0]    = faces[FRONT][0];
		faces[TOP][3]    = faces[FRONT][3];

		faces[FRONT][0]  = faces[BOTTOM][0];
		faces[FRONT][3]  = faces[BOTTOM][3];

		faces[BOTTOM][0] = faces[BACK][0];
		faces[BOTTOM][3] = faces[BACK][3];

		faces[BACK][0]   = t0;
		faces[BACK][3]   = t1;

	}

	void
	rotate_bottom() {
		char t0, t1;

		t0               = faces[BOTTOM][0];
		faces[BOTTOM][0] = faces[BOTTOM][3];
		faces[BOTTOM][3] = faces[BOTTOM][2];
		faces[BOTTOM][2] = faces[BOTTOM][1];
		faces[BOTTOM][1] = t0;

		t0               = faces[FRONT][2];
		t1               = faces[FRONT][3];

		faces[FRONT][2]  = faces[LEFT][2];
		faces[FRONT][3]  = faces[LEFT][3];

		faces[LEFT][2]   = faces[BACK][0];
		faces[LEFT][3]   = faces[BACK][1];

		faces[BACK][0]   = faces[RIGHT][2];
		faces[BACK][1]   = faces[RIGHT][3];

		faces[RIGHT][2]  = t0;
		faces[RIGHT][3]  = t1;

	}

	void
	rotate_top() {
		char t0, t1;

		t0               = faces[BOTTOM][0];
		faces[BOTTOM][0] = faces[BOTTOM][1];
		faces[BOTTOM][1] = faces[BOTTOM][2];
		faces[BOTTOM][2] = faces[BOTTOM][3];
		faces[BOTTOM][3] = t0;

		t0               = faces[FRONT][3];
		t1               = faces[FRONT][2];

		faces[FRONT][3]  = faces[RIGHT][3];
		faces[FRONT][2]  = faces[RIGHT][2];

		faces[RIGHT][3]  = faces[BACK][1];
		faces[RIGHT][2]  = faces[BACK][0];

		faces[BACK][0]   = faces[LEFT][2];
		faces[BACK][1]   = faces[LEFT][3];

		faces[LEFT][2]   = t1;
		faces[LEFT][3]   = t0;
	}

	bool
	check_solved() {
		int i;

		for (i = 0; i < 6; i++) {
			if (! (faces[i][0] == faces[i][1] and
			       faces[i][1] == faces[i][2] and
			       faces[i][2] == faces[i][3])) {

				return false;
			}
		}

		return true;
	}

	void
	dump_faces() {
		int i,j;
		std::string faces_name[] = {"FRONT\t", "BACK\t", "LEFT\t", "RIGHT\t", "TOP\t", "BOTTOM\t" };

		for (i = 0; i < 6; i++) {
			std::cout << faces_name[i];
			for (j = 0; j < 4; j++) {
				std::cout << faces[i][j] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

};

int
main() {
	std::queue<cube *> solutions;
	cube *cur;
	int attempt = 1;
	std::unordered_map<std::string, bool> already_visited;

	srand (time(NULL));

	cur = new cube();
	solutions.push(cur);

	std::cout << "solving.." << std::endl;

	int k = 0;

	while (not solutions.empty()) {
		cur = solutions.front();
		solutions.pop();

		cube *new_conf;
		std::string *faces_string;

		if (cur->depth > k) {
			k = (int) cur->depth;
			attempt = 1;
			std::cout << "\nk: " << (int) k << std::endl;
		}

		new_conf = new cube(*cur);
		new_conf->rotate_left();
		new_conf->depth++;

		faces_string = new std::string((const char *) new_conf->faces, 24);

		if (already_visited.count(*faces_string) == 0) {
			solutions.push(new_conf);
			already_visited.emplace(*faces_string, true);
		}

		delete faces_string;

		new_conf = new cube(*cur);
		new_conf->rotate_right();
		new_conf->depth++;

		faces_string = new std::string((const char *) new_conf->faces, 24);

		if (already_visited.count(*faces_string) == 0) {
			solutions.push(new_conf);
			already_visited.emplace(*faces_string, true);
		}

		delete faces_string;

		new_conf = new cube(*cur);
		new_conf->rotate_top();
		new_conf->depth++;


		faces_string = new std::string((const char *) new_conf->faces, 24);

		if (already_visited.count(*faces_string) == 0) {
			solutions.push(new_conf);
			already_visited.emplace(*faces_string, true);
		}

		delete faces_string;

		new_conf = new cube(*cur);
		new_conf->rotate_bottom();
		new_conf->depth++;


		faces_string = new std::string((const char *) new_conf->faces, 24);

		if (already_visited.count(*faces_string) == 0) {
			solutions.push(new_conf);
			already_visited.emplace(*faces_string, true);
		}

		delete faces_string;

		new_conf = new cube(*cur);
		new_conf->rotate_front();
		new_conf->depth++;


		faces_string = new std::string((const char *) new_conf->faces, 24);

		if (already_visited.count(*faces_string) == 0) {
			solutions.push(new_conf);
			already_visited.emplace(*faces_string, true);
		}

		delete faces_string;

		new_conf = new cube(*cur);
		new_conf->rotate_back();
		new_conf->depth++;

		faces_string = new std::string((const char *) new_conf->faces, 24);

		if (already_visited.count(*faces_string) == 0) {
			solutions.push(new_conf);
			already_visited.emplace(*faces_string, true);
		}

		delete faces_string;

		std::cout << "\rattempt: " << attempt << std::flush;
		attempt++;

		delete cur;
	}

	return 0;
}

