#define _CRT_SECURE_NO_WARNINGS

#include <bangtal>
#include <cstdlib>
#include <ctime>

using namespace bangtal;

TimerPtr timer1, timer2, timer_inst, timer_show1, timer_show2;
ScenePtr scene = Scene::create("Mouth_Len", "Images/background.png");
ObjectPtr start = 0;
ObjectPtr end = 0;
ObjectPtr yes_play_song = 0;
ObjectPtr no_play_song = 0;
ObjectPtr notice = 0;
ObjectPtr i_long = 0;
ObjectPtr i_short = 0;
SoundPtr song = 0;
int arr_20[20] = { 0, }, result_your[40] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
int trial = 20; int count = 0;
int num_right = 0; int time_inc = 0;

void song_object() {
	yes_play_song = Object::create("Images/Play_Song_Yes.png", scene, 800, 700); yes_play_song->setScale(0.5);
	yes_play_song->setOnMouseCallback([&](auto, auto, auto, auto)->bool {
		song->play(true);
		yes_play_song->hide();
		no_play_song->show();
		return true;
		});

	no_play_song = Object::create("Images/Play_Song_No.png", scene, 800, 700); no_play_song->setScale(0.5);
	no_play_song->setOnMouseCallback([&](auto, auto, auto, auto)->bool {
		song->stop();
		no_play_song->hide();
		yes_play_song->show();
		return true;
		});

	yes_play_song->hide();
}

void makearray_start() {
	printf("\n\n\n");
	printf("======================================================================");
	printf("\n\n\n");

	srand((unsigned int)time(NULL));
	for (int i = 0; i < 20; i++)
	{
		arr_20[i] = rand() % 2;
	}
}

void reset() {
	trial = 20; count = 0;
	timer_inst = Timer::create(42.0f);
	timer_inst->setOnTimerCallback([&](auto)->bool {
		makeresult();
		return true;
		});
	timer_inst->start();
	time_inc = -1;
	timer1->set(1.95f); timer1->start();
	timer_show1->set(time_inc); timer_show1->start();
}

void makeresult() {
	printf("\n\n");
	num_right = 0;
	printf("Correct Answer is :\n\n");
	for (int i = 0; i < 20; i++)
	{
		printf(" %d", arr_20[i]);
	}
	printf("\n\nYour Answer is :\n\n");
	for (int i = 0; i < 40; i++)
	{
		if (i % 2 == 0)
		{
			if (result_your[i] != (-1))
			{
				printf(" %d", result_your[i]);
			}
			else
			{
				printf("%d", result_your[i]);
			}
		}
	}
	printf("\n\nwhether your answer is 'o' or 'x'\n\n\n");
	for (int i = 0; i < 20; i++)
	{
		if (arr_20[i] == result_your[2 * i])
		{
			printf("O ");
			num_right++;
		}
		else
		{
			printf("X ");
		}
	}
	char message_in[100];
	sprintf(message_in, "Your score is %d out of 20 !!!", num_right);
	showMessage(message_in);
}

void init_game()
{
	scene->setOnKeyboardCallback([&](ScenePtr scene, KeyCode key, bool pressed)->bool {
		if (count < 40)
		{
			if (key == KeyCode::KEY_LEFT_ARROW)
				result_your[count] = 0;
			if (key == KeyCode::KEY_RIGHT_ARROW)
				result_your[count] = 1;
			count++;
		}
		return true;
		});

	timer_show1 = Timer::create(time_inc);
	timer_show1->setOnTimerCallback([&](auto)->bool {
		time_inc++;
		timer_show2->set(1.95f);
		timer_show2->start();
		timer_show1->set(time_inc);
		showTimer(timer_show1);
		if (time_inc > 19) {
			timer_show1->stop();
		}
		return true;
		});

	timer_show2 = Timer::create(1.95f);
	timer_show2->setOnTimerCallback([&](auto)->bool {
		timer_show1->set(0);
		timer_show1->start();
		if (time_inc > 19) {
			timer_show1->stop();
		}
		return true;
		});

	timer1 = Timer::create(1.95f);
	timer1->setOnTimerCallback([&](auto)->bool {
		if (trial > 0) {
			timer2->set(1.0f); timer2->start();
			timer1->set(1.95f);
			timer1->start();
		}
		trial--;
		i_long->hide();
		i_short->hide();
		return true;
		});

	timer2 = Timer::create(1.0f);
	timer2->setOnTimerCallback([&](auto)->bool {
		if (arr_20[trial] == 0)
		{
			i_long->show();
		}
		if (arr_20[trial] == 1)
		{
			i_short->show();
		}
		return true;
		});

	start = Object::create("Images/start.png", scene, 750, 150);
	start->setOnMouseCallback([&](auto, auto, auto, auto)->bool {
		reset();
		makearray_start();
		return true;
		});

	end = Object::create("Images/end.png", scene, 750, 100);
	end->setOnMouseCallback([&](auto, auto, auto, auto)->bool {
		endGame();
		return true;
		});

	startGame(scene);
}

int main()
{
	song = Sound::create("Sound/x-mas.mp3"); song->play(true);
	song_object();

	i_long = Object::create("Images/i_long.png", scene, 300, 300); i_long->setScale(0.5f); i_long->hide();        //0 
	i_short = Object::create("Images/i_short.png", scene, 300, 300); i_short->setScale(0.5f); i_short->hide();    //1

	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

	init_game();
	return 0;
}