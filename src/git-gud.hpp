#ifndef GIT_GUD_HPP
#define GIT_GUD_HPP

#include <memory>
#include <vector>
#include <map>

namespace git_gud
{

	/**
	 * Commits make the nodes of the GitTree. Each may have several
	 * parents and several children. Each MUST have a unique ID.
	 *
	 * @author Michael Bianconi
	 */
	class Commit
	{

		private:

			int commitID;
			int branchID;

			std::vector<std::shared_ptr<Commit> > parents;
			std::vector<std::shared_ptr<Commit> > children;

			/**
			 * @return Returns a unique, sequential ID.
			 */
			int generateID();

		public:

			/**
			 * Creates a new Commit on the specified branch and with
			 * a unique ID.
			 *
			 * @param branchID The ID of the branch.
			 */
			Commit(int branchID); // autogenerated ID

			/**
			 * Creates a new Commit on the specified branch.
			 *
			 * @param branchID The ID of the branch.
			 * @param commitID The ID of the commit.
			 */
			Commit(int branchID, int commitID); // pregenerated ID

			int getID() const;
			int getBranch() const;
			int getNumParents() const;
			int getNumChildren() const;
			bool isMergeCommit() const;
			bool isNewBranch() const;

			std::vector<std::shared_ptr<Commit> >& getParents();
			std::vector<std::shared_ptr<Commit> >& getChildren();

			/**
			 * Adds the given commit as a parent. Does NOT update the
			 * parent commit to reflect the change.
			 *
			 * @param parent Parent commit to add.
			 * @throws std::invalid_argument if adding itself as a parent.
			 */
			void addParent(std::shared_ptr<Commit> parent);

			/**
			 * Adds the given commit as a child. Does NOT update the
			 * child commit to reflect the change.
			 *
			 * @param child Child commit to add.
			 * @throws std::invalid_argument if adding itself as a child.
			 */
			void addChild(std::shared_ptr<Commit> child);

			/**
			 * Removes the parent commit from this object.
			 *
			 * @param id ID of the parent commit.
			 * @throws std::invalid_argument if parent does not exist.
			 */
			void removeParent(int id);

			/**
			 * Removes the child commit from this object.
			 *
			 * @param id ID of the child commit.
			 * @throws std::invalid_argument if child does not exist.
			 */
			void removeChild(int id);

			void print();
	};

	class GitTree
	{
		private:

			std::shared_ptr<Commit> head;
			std::vector<std::shared_ptr<Commit> > commits;
			int numBranches = 0;

			int generateBranchID();

		public:

			GitTree();

			std::shared_ptr<Commit> getHead() const;
			std::shared_ptr<Commit> getCommit(int ID) const;
			std::shared_ptr<Commit> getLatest() const;
			std::shared_ptr<Commit> getLatest(int branchID) const;

			std::vector<std::shared_ptr<Commit> >& getAllCommits();
			int getNumBranches() const;
			int getNumCommits() const;

			/**
			 * Generates a new Commit as a child of the head.
			 * Checks out the new Commit.
			 *
			 * @return Returns the generated Commit.
			 * @throws std::invalid_argument if HEAD already has a child.
			 */
			std::shared_ptr<Commit> addCommit();

			/**
			 * Generates a new Commit as a child of the specified parent,
			 * on the same branch. Checks out the new Commit.
`			 *
			 * @param parentID ID of the commit to add to.
			 * @throws std::invalid_argument if parent already has a child,
			 *         or does not exist.
			 */
			std::shared_ptr<Commit> addCommit(int parentID);


			/**
			 * Creates a new branch at HEAD.
			 */
			std::shared_ptr<Commit> addCommitNewBranch();

			/**
			 * Generates a new Commit as a child of the specified parent,
			 * on a new branch.
			 *
			 * @throws std::invalid_argument if parent not found.
			 */
			std::shared_ptr<Commit> addCommitNewBranch(int parentID);

			/**
			 * Sets the head of the tree.
			 *
			 * @param commitID ID of the commit to set as the head.
			 * @throws std::invalid_argument if commitID does not exist.
			 */
			void checkout(int commitID);

			/**
			 * Sets the head of the tree.
			 *
			 * @param Commit to set.
			 */
			void checkout(std::shared_ptr<Commit> commit);

			/**
			 * Creates a new commit, appended to the head and with
			 * the given commit as its other parent.
			 *
			 * @param otherID ID of the commit to merge into the head.
			 * @return Returns the new Commit.
			 * @throws std::invalid_argument if otherID doesn't exist.
			 */
			std::shared_ptr<Commit> merge(int otherID);

			/**
			 * Creates a new commit, appended to the parentID and
			 * merged with the other.
			 *
			 * @param parentID ID of the parent to merge onto.
			 * @param otherID ID of the brange to merge from.
			 * @return Return's the newly created commit.
			 * @throws std::invalid_argument if either commit doesn't exist.
			 */
			std::shared_ptr<Commit> merge(int parentID, int otherID);

			/**
			 * Removes the last Commit from the tree. If there is
			 * only one node, do nothing.
			 */
			void undo();

			void print() const;
	};
}

#endif