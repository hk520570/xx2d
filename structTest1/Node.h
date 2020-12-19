﻿#pragma once
#include "Ref.h"

struct SceneTree;
struct Signal;
struct Node : Ref<Node> {
	/*********************************************************************/
	// constructs

	Node(SceneTree* const& tree);
	virtual ~Node() = default;
	Node(Node const&) = delete;
	Node& operator=(Node const&) = delete;

	/*********************************************************************/
	// fields

	SceneTree* const tree;
	bool entered = false;
	xx::Weak<Node> parent;
	std::vector<xx::Shared<Node>> children;
	std::string name;
	std::unordered_map<std::string_view, xx::Weak<Node>> signalReceivers;

	/*********************************************************************/
	// generic events

	virtual void EnterTree();
	virtual void ExitTree();
	virtual void Ready();
	virtual void Process(float delta);

	void CallEnterTree();
	void CallExitTree();
	void CallReady();
	void CallProcess(float delta);

	/*********************************************************************/
	// utils

	SceneTree* GetTree() const;
	xx::Shared<Node> GetParent();
	xx::Shared<Node> GetNode(std::string_view const& path) const;

	void AddChild(xx::Shared<Node> const& node);
	void RemoveChild(xx::Shared<Node> const& node);
	void Remove();

	void MoveChild(xx::Shared<Node> const& node, size_t const& index);
	void MoveToLast();

	void PrintTreePretty(std::string const& prefix = "", bool const& last = true) const;

	void Connect(std::string_view const& signalName, xx::Shared<Node> const& receiver);
	virtual void Receive(xx::Shared<Node> const& sender, Signal const& sig);
};
