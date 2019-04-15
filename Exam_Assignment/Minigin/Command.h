#pragma once
#include <iostream>
class Command
{
public:
	Command();
	virtual ~Command();
	virtual bool execute();
};
class JumpCommand : public Command
{
public:
	virtual bool execute() override { std::cout << "Jump" << std::endl; return false; }
};

class FireCommand : public Command
{
public:
	virtual bool execute() override { std::cout << "Fire" << std::endl; return false; }
};

class DuckCommand : public Command
{
public:
	virtual bool execute() override { std::cout << "Duck" << std::endl; return false;}
};

class ExitCommand : public Command
{
public:
	virtual bool execute() override { std::cout << "Exit" << std::endl; return true;}
};