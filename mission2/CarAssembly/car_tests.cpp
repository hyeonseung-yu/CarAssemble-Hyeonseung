#include "gmock/gmock.h"
#include "car.cpp"
#include "engine.cpp"
#include "brake.cpp"
#include "steering.cpp"
#include "assembler.cpp"

TEST(CAR_TEST, ValidCarRange) {
	Car car;
	bool ret = car.isValidTypeRange(2);
	EXPECT_TRUE(ret);
}

TEST(CAR_TEST, InvalidCarRange) {
	Car car;
	bool ret = car.isValidTypeRange(4);
	EXPECT_FALSE(ret);
}

TEST(CAR_TEST, NumberOfCars) {
	Car car;
	int ret = car.numberOfAvailableTypes();
	EXPECT_EQ(ret, 3);
}

TEST(CAR_TEST, CarTypeName) {
	Car car;
	std::string ret = car.getTypeName(1);
	EXPECT_EQ(ret, "Sedan");
	ret = car.getTypeName(2);
	EXPECT_EQ(ret, "SUV");
	ret = car.getTypeName(3);
	EXPECT_EQ(ret, "Truck");
	ret = car.getTypeName(4);
	EXPECT_EQ(ret, "INVALID TYPE");
}

TEST(CAR_TEST, CarTypeSetGet) {
	Car car;
	car.setType(2);
	int ret = car.getType();
	EXPECT_EQ(ret, 2);
}



TEST(ENGINE_TEST, ValidEngineRange) {
	Engine engine;
	bool ret = engine.isValidTypeRange(3);
	EXPECT_TRUE(ret);
}

TEST(ENGINE_TEST, InvalidEngineRange) {
	Engine engine;
	bool ret = engine.isValidTypeRange(5);
	EXPECT_FALSE(ret);
}

TEST(ENGINE_TEST, NumberOfEngines) {
	Engine engine;
	int ret = engine.numberOfAvailableTypes();
	EXPECT_EQ(ret, 4);
}


TEST(ENGINE_TEST, EngineTypeName) {
	Engine engine;
	std::string ret = engine.getTypeName(1);
	EXPECT_EQ(ret, "GM");
	ret = engine.getTypeName(2);
	EXPECT_EQ(ret, "TOYOTA");
	ret = engine.getTypeName(3);
	EXPECT_EQ(ret, "WIA");
	ret = engine.getTypeName(4);
	EXPECT_EQ(ret, "고장난 엔진");
	ret = engine.getTypeName(5);
	EXPECT_EQ(ret, "INVALID TYPE");
}

TEST(ENGINE_TEST, EngineTypeSetGet) {
	Engine engine;
	engine.setType(2);
	int ret = engine.getType();
	EXPECT_EQ(ret, 2);
}

TEST(ENGINE_TEST, EngineBroken) {
	Engine engine;
	engine.setType(4);
	bool ret = engine.isEngineBroken();
	EXPECT_TRUE(ret);
}


TEST(BRAKE_TEST, ValidBrakeRange) {
	Brake brake;
	bool ret = brake.isValidTypeRange(3);
	EXPECT_TRUE(ret);
}

TEST(BRAKE_TEST, InvalidBrakeRange) {
	Brake brake;
	bool ret = brake.isValidTypeRange(4);
	EXPECT_FALSE(ret);
}

TEST(BRAKE_TEST, NumberOfBrakes) {
	Brake brake;
	int ret = brake.numberOfAvailableTypes();
	EXPECT_EQ(ret, 3);
}

TEST(BRAKE_TEST, BrakeTypeName) {
	Brake brake;
	std::string ret = brake.getTypeName(1);
	EXPECT_EQ(ret, "MANDO");
	ret = brake.getTypeName(2);
	EXPECT_EQ(ret, "CONTINENTAL");
	ret = brake.getTypeName(3);
	EXPECT_EQ(ret, "BOSCH");
	ret = brake.getTypeName(4);
	EXPECT_EQ(ret, "INVALID TYPE");
}

TEST(BRAKE_TEST, BrakeTypeSetGet) {
	Brake brake;
	brake.setType(2);
	int ret = brake.getType();
	EXPECT_EQ(ret, 2);
}




TEST(STEERING_TEST, ValidSteeringRange) {
	Steering steering;
	bool ret = steering.isValidTypeRange(2);
	EXPECT_TRUE(ret);
}

TEST(STEERING_TEST, InvalidSteeringRange) {
	Steering steering;
	bool ret = steering.isValidTypeRange(3);
	EXPECT_FALSE(ret);
}

TEST(STEERING_TEST, NumberOfSteerings) {
	Steering steering;
	int ret = steering.numberOfAvailableTypes();
	EXPECT_EQ(ret, 2);
}

TEST(STEERING_TEST, SteeringTypeName) {
	Steering steering;
	std::string ret = steering.getTypeName(1);
	EXPECT_EQ(ret, "BOSCH");
	ret = steering.getTypeName(2);
	EXPECT_EQ(ret, "MOBIS");
	ret = steering.getTypeName(3);
	EXPECT_EQ(ret, "INVALID TYPE");
}

TEST(STEERING_TEST, SteeringTypeSetGet) {
	Steering steering;
	steering.setType(2);
	int ret = steering.getType();
	EXPECT_EQ(ret, 2);
}


TEST(Assembler_TEST, ValidAssemblyTest) {
	Car car;
	Engine engine;
	Brake brake;
	Steering steering;
	Assembler& assembler = Assembler::getInstance();
	
	car.setType(SEDAN);
	brake.setType(CONTINENTAL);
	bool ret = assembler.isValidAssembly(car, engine, brake, steering);
	EXPECT_FALSE(ret);

	car.setType(SUV);
	engine.setType(TOYOTA);
	ret = assembler.isValidAssembly(car, engine, brake, steering);
	EXPECT_FALSE(ret);

	car.setType(TRUCK);
	engine.setType(WIA);
	ret = assembler.isValidAssembly(car, engine, brake, steering);
	EXPECT_FALSE(ret);

	car.setType(TRUCK);
	engine.setType(TOYOTA);
	brake.setType(MANDO);
	ret = assembler.isValidAssembly(car, engine, brake, steering);
	EXPECT_FALSE(ret);

	car.setType(SUV);
	engine.setType(GM);
	brake.setType(BOSCH_B);
	steering.setType(MOBIS);
	ret = assembler.isValidAssembly(car, engine, brake, steering);
	EXPECT_FALSE(ret);

	car.setType(SUV);
	engine.setType(GM);
	brake.setType(MANDO);
	steering.setType(BOSCH_S);
	ret = assembler.isValidAssembly(car, engine, brake, steering);
	EXPECT_TRUE(ret);
}



TEST(Assembler_TEST, AssemblyResultStrTest) {
	Car car;
	Engine engine;
	Brake brake;
	Steering steering;
	Assembler& assembler = Assembler::getInstance();

	car.setType(SEDAN);
	brake.setType(CONTINENTAL);
	std::string ret = assembler.generateTestResultString(car, engine, brake, steering);
	EXPECT_EQ(ret, "FAIL\nSedan에는 Continental제동장치 사용 불가");

	car.setType(SUV);
	engine.setType(TOYOTA);
	ret = assembler.generateTestResultString(car, engine, brake, steering);
	EXPECT_EQ(ret, "FAIL\nSUV에는 TOYOTA엔진 사용 불가");

	car.setType(TRUCK);
	engine.setType(WIA);
	ret = assembler.generateTestResultString(car, engine, brake, steering);
	EXPECT_EQ(ret, "FAIL\nTruck에는 WIA엔진 사용 불가");

	car.setType(TRUCK);
	engine.setType(TOYOTA);
	brake.setType(MANDO);
	ret = assembler.generateTestResultString(car, engine, brake, steering);
	EXPECT_EQ(ret, "FAIL\nTruck에는 Mando제동장치 사용 불가");

	car.setType(SEDAN);
	engine.setType(GM);
	brake.setType(BOSCH_B);
	steering.setType(MOBIS);
	ret = assembler.generateTestResultString(car, engine, brake, steering);
	EXPECT_EQ(ret, "FAIL\nBosch제동장치에는 Bosch조향장치 이외 사용 불가");

	car.setType(SUV);
	engine.setType(GM);
	brake.setType(MANDO);
	steering.setType(BOSCH_S);
	ret = assembler.generateTestResultString(car, engine, brake, steering);
	EXPECT_EQ(ret, "PASS");
}