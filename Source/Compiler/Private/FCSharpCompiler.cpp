﻿#include "FCSharpCompiler.h"
#include "FCSharpCompilerRunnable.h"

FCSharpCompiler::FCSharpCompiler():
	Runnable(nullptr)
{
	Runnable = new FCSharpCompilerRunnable();

	FRunnableThread::Create(Runnable, TEXT("CSharpCompiler"));
}

FCSharpCompiler::~FCSharpCompiler()
{
	if (Runnable != nullptr)
	{
		delete Runnable;

		Runnable = nullptr;
	}
}

FCSharpCompiler& FCSharpCompiler::Get()
{
	static FCSharpCompiler Compiler;

	return Compiler;
}

void FCSharpCompiler::Compile() const
{
	if (Runnable != nullptr)
	{
		Runnable->EnqueueTask();
	}
}

void FCSharpCompiler::Compile(const TArray<FFileChangeData>& FileChangeData) const
{
	if (Runnable != nullptr)
	{
		Runnable->EnqueueTask(FileChangeData);
	}
}

bool FCSharpCompiler::IsCompiling() const
{
	return Runnable != nullptr ? Runnable->IsCompiling() : false;
}
